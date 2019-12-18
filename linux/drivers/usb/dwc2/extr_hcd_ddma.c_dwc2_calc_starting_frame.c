#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;
struct dwc2_qh {scalar_t__ dev_speed; } ;
struct dwc2_hsotg {int /*<<< orphan*/  frame_number; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_HIGH ; 
 int dwc2_frame_num_inc (int /*<<< orphan*/ ,int) ; 
 int dwc2_full_frame_num (int) ; 
 int /*<<< orphan*/  dwc2_hcd_get_frame_number (struct dwc2_hsotg*) ; 
 int dwc2_micro_frame_num (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 dwc2_calc_starting_frame(struct dwc2_hsotg *hsotg,
				    struct dwc2_qh *qh, u16 *skip_frames)
{
	u16 frame;

	hsotg->frame_number = dwc2_hcd_get_frame_number(hsotg);

	/*
	 * next_active_frame is always frame number (not uFrame) both in FS
	 * and HS!
	 */

	/*
	 * skip_frames is used to limit activated descriptors number
	 * to avoid the situation when HC services the last activated
	 * descriptor firstly.
	 * Example for FS:
	 * Current frame is 1, scheduled frame is 3. Since HC always fetches
	 * the descriptor corresponding to curr_frame+1, the descriptor
	 * corresponding to frame 2 will be fetched. If the number of
	 * descriptors is max=64 (or greather) the list will be fully programmed
	 * with Active descriptors and it is possible case (rare) that the
	 * latest descriptor(considering rollback) corresponding to frame 2 will
	 * be serviced first. HS case is more probable because, in fact, up to
	 * 11 uframes (16 in the code) may be skipped.
	 */
	if (qh->dev_speed == USB_SPEED_HIGH) {
		/*
		 * Consider uframe counter also, to start xfer asap. If half of
		 * the frame elapsed skip 2 frames otherwise just 1 frame.
		 * Starting descriptor index must be 8-aligned, so if the
		 * current frame is near to complete the next one is skipped as
		 * well.
		 */
		if (dwc2_micro_frame_num(hsotg->frame_number) >= 5) {
			*skip_frames = 2 * 8;
			frame = dwc2_frame_num_inc(hsotg->frame_number,
						   *skip_frames);
		} else {
			*skip_frames = 1 * 8;
			frame = dwc2_frame_num_inc(hsotg->frame_number,
						   *skip_frames);
		}

		frame = dwc2_full_frame_num(frame);
	} else {
		/*
		 * Two frames are skipped for FS - the current and the next.
		 * But for descriptor programming, 1 frame (descriptor) is
		 * enough, see example above.
		 */
		*skip_frames = 1;
		frame = dwc2_frame_num_inc(hsotg->frame_number, 2);
	}

	return frame;
}