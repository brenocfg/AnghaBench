#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  vb2_buf; int /*<<< orphan*/  sequence; int /*<<< orphan*/  field; } ;
struct pwc_frame_buf {int filled; TYPE_1__ vb; scalar_t__ data; } ;
struct pwc_device {int type; scalar_t__ drop_frames; unsigned char vmirror; int frame_total_size; int /*<<< orphan*/  vframe_count; scalar_t__ vsync; struct pwc_frame_buf* fill_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWC_DEBUG_FLOW (char*,int) ; 
 int /*<<< orphan*/  PWC_TRACE (char*) ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  pwc_snapshot_button (struct pwc_device*,unsigned char) ; 
 int /*<<< orphan*/  vb2_buffer_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwc_frame_complete(struct pwc_device *pdev)
{
	struct pwc_frame_buf *fbuf = pdev->fill_buf;

	/* The ToUCam Fun CMOS sensor causes the firmware to send 2 or 3 bogus
	   frames on the USB wire after an exposure change. This conditition is
	   however detected  in the cam and a bit is set in the header.
	   */
	if (pdev->type == 730) {
		unsigned char *ptr = (unsigned char *)fbuf->data;

		if (ptr[1] == 1 && ptr[0] & 0x10) {
			PWC_TRACE("Hyundai CMOS sensor bug. Dropping frame.\n");
			pdev->drop_frames += 2;
		}
		if ((ptr[0] ^ pdev->vmirror) & 0x01) {
			pwc_snapshot_button(pdev, ptr[0] & 0x01);
		}
		if ((ptr[0] ^ pdev->vmirror) & 0x02) {
			if (ptr[0] & 0x02)
				PWC_TRACE("Image is mirrored.\n");
			else
				PWC_TRACE("Image is normal.\n");
		}
		pdev->vmirror = ptr[0] & 0x03;
		/* Sometimes the trailer of the 730 is still sent as a 4 byte packet
		   after a short frame; this condition is filtered out specifically. A 4 byte
		   frame doesn't make sense anyway.
		   So we get either this sequence:
		   drop_bit set -> 4 byte frame -> short frame -> good frame
		   Or this one:
		   drop_bit set -> short frame -> good frame
		   So we drop either 3 or 2 frames in all!
		   */
		if (fbuf->filled == 4)
			pdev->drop_frames++;
	} else if (pdev->type == 740 || pdev->type == 720) {
		unsigned char *ptr = (unsigned char *)fbuf->data;
		if ((ptr[0] ^ pdev->vmirror) & 0x01) {
			pwc_snapshot_button(pdev, ptr[0] & 0x01);
		}
		pdev->vmirror = ptr[0] & 0x03;
	}

	/* In case we were instructed to drop the frame, do so silently. */
	if (pdev->drop_frames > 0) {
		pdev->drop_frames--;
	} else {
		/* Check for underflow first */
		if (fbuf->filled < pdev->frame_total_size) {
			PWC_DEBUG_FLOW("Frame buffer underflow (%d bytes); discarded.\n",
				       fbuf->filled);
		} else {
			fbuf->vb.field = V4L2_FIELD_NONE;
			fbuf->vb.sequence = pdev->vframe_count;
			vb2_buffer_done(&fbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);
			pdev->fill_buf = NULL;
			pdev->vsync = 0;
		}
	} /* !drop_frames */
	pdev->vframe_count++;
}