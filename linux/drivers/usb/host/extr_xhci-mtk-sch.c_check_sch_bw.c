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
typedef  scalar_t__ u32 ;
struct usb_device {scalar_t__ speed; } ;
struct mu3h_sch_ep_info {scalar_t__ esit; scalar_t__ cs_count; scalar_t__ num_budget_microframes; scalar_t__ offset; } ;
struct mu3h_sch_bw_info {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ HS_BW_BOUNDARY ; 
 scalar_t__ SSP_BW_BOUNDARY ; 
 scalar_t__ SS_BW_BOUNDARY ; 
 scalar_t__ USB_SPEED_SUPER ; 
 scalar_t__ USB_SPEED_SUPER_PLUS ; 
 int check_sch_tt (struct usb_device*,struct mu3h_sch_ep_info*,scalar_t__) ; 
 scalar_t__ get_max_bw (struct mu3h_sch_bw_info*,struct mu3h_sch_ep_info*,scalar_t__) ; 
 scalar_t__ is_fs_or_ls (scalar_t__) ; 
 int /*<<< orphan*/  update_bus_bw (struct mu3h_sch_bw_info*,struct mu3h_sch_ep_info*,int) ; 
 int /*<<< orphan*/  update_sch_tt (struct usb_device*,struct mu3h_sch_ep_info*) ; 

__attribute__((used)) static int check_sch_bw(struct usb_device *udev,
	struct mu3h_sch_bw_info *sch_bw, struct mu3h_sch_ep_info *sch_ep)
{
	u32 offset;
	u32 esit;
	u32 min_bw;
	u32 min_index;
	u32 worst_bw;
	u32 bw_boundary;
	u32 min_num_budget;
	u32 min_cs_count;
	bool tt_offset_ok = false;
	int ret;

	esit = sch_ep->esit;

	/*
	 * Search through all possible schedule microframes.
	 * and find a microframe where its worst bandwidth is minimum.
	 */
	min_bw = ~0;
	min_index = 0;
	min_cs_count = sch_ep->cs_count;
	min_num_budget = sch_ep->num_budget_microframes;
	for (offset = 0; offset < esit; offset++) {
		if (is_fs_or_ls(udev->speed)) {
			ret = check_sch_tt(udev, sch_ep, offset);
			if (ret)
				continue;
			else
				tt_offset_ok = true;
		}

		if ((offset + sch_ep->num_budget_microframes) > sch_ep->esit)
			break;

		worst_bw = get_max_bw(sch_bw, sch_ep, offset);
		if (min_bw > worst_bw) {
			min_bw = worst_bw;
			min_index = offset;
			min_cs_count = sch_ep->cs_count;
			min_num_budget = sch_ep->num_budget_microframes;
		}
		if (min_bw == 0)
			break;
	}

	if (udev->speed == USB_SPEED_SUPER_PLUS)
		bw_boundary = SSP_BW_BOUNDARY;
	else if (udev->speed == USB_SPEED_SUPER)
		bw_boundary = SS_BW_BOUNDARY;
	else
		bw_boundary = HS_BW_BOUNDARY;

	/* check bandwidth */
	if (min_bw > bw_boundary)
		return -ERANGE;

	sch_ep->offset = min_index;
	sch_ep->cs_count = min_cs_count;
	sch_ep->num_budget_microframes = min_num_budget;

	if (is_fs_or_ls(udev->speed)) {
		/* all offset for tt is not ok*/
		if (!tt_offset_ok)
			return -ERANGE;

		update_sch_tt(udev, sch_ep);
	}

	/* update bus bandwidth info */
	update_bus_bw(sch_bw, sch_ep, 1);

	return 0;
}