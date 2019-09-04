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
typedef  int u32 ;
struct timeval {int dummy; } ;
struct omap_vout_device {int field_id; TYPE_1__* next_frm; TYPE_1__* cur_frm; int /*<<< orphan*/  dma_queue; scalar_t__ first_int; } ;
struct TYPE_2__ {int /*<<< orphan*/  done; int /*<<< orphan*/  state; struct timeval ts; } ;

/* Variables and functions */
 unsigned int DISPC_IRQ_EVSYNC_EVEN ; 
 unsigned int DISPC_IRQ_EVSYNC_ODD ; 
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omapvid_handle_interlace_display(struct omap_vout_device *vout,
		unsigned int irqstatus, struct timeval timevalue)
{
	u32 fid;

	if (vout->first_int) {
		vout->first_int = 0;
		goto err;
	}

	if (irqstatus & DISPC_IRQ_EVSYNC_ODD)
		fid = 1;
	else if (irqstatus & DISPC_IRQ_EVSYNC_EVEN)
		fid = 0;
	else
		goto err;

	vout->field_id ^= 1;
	if (fid != vout->field_id) {
		if (fid == 0)
			vout->field_id = fid;
	} else if (0 == fid) {
		if (vout->cur_frm == vout->next_frm)
			goto err;

		vout->cur_frm->ts = timevalue;
		vout->cur_frm->state = VIDEOBUF_DONE;
		wake_up_interruptible(&vout->cur_frm->done);
		vout->cur_frm = vout->next_frm;
	} else {
		if (list_empty(&vout->dma_queue) ||
				(vout->cur_frm != vout->next_frm))
			goto err;
	}

	return vout->field_id;
err:
	return 0;
}