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
typedef  int u32 ;
struct usb_device {int dummy; } ;
struct mu3h_sch_tt {int /*<<< orphan*/  split_bit_map; } ;
struct mu3h_sch_ep_info {scalar_t__ ep_type; int cs_count; int num_budget_microframes; int esit; int /*<<< orphan*/  maxpkt; struct mu3h_sch_tt* sch_tt; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ERANGE ; 
 int /*<<< orphan*/  FS_PAYLOAD_MAX ; 
 scalar_t__ ISOC_IN_EP ; 
 scalar_t__ ISOC_OUT_EP ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_sch_tt(struct usb_device *udev,
	struct mu3h_sch_ep_info *sch_ep, u32 offset)
{
	struct mu3h_sch_tt *tt = sch_ep->sch_tt;
	u32 extra_cs_count;
	u32 fs_budget_start;
	u32 start_ss, last_ss;
	u32 start_cs, last_cs;
	int i;

	start_ss = offset % 8;
	fs_budget_start = (start_ss + 1) % 8;

	if (sch_ep->ep_type == ISOC_OUT_EP) {
		last_ss = start_ss + sch_ep->cs_count - 1;

		/*
		 * usb_20 spec section11.18:
		 * must never schedule Start-Split in Y6
		 */
		if (!(start_ss == 7 || last_ss < 6))
			return -ERANGE;

		for (i = 0; i < sch_ep->cs_count; i++)
			if (test_bit(offset + i, tt->split_bit_map))
				return -ERANGE;

	} else {
		u32 cs_count = DIV_ROUND_UP(sch_ep->maxpkt, FS_PAYLOAD_MAX);

		/*
		 * usb_20 spec section11.18:
		 * must never schedule Start-Split in Y6
		 */
		if (start_ss == 6)
			return -ERANGE;

		/* one uframe for ss + one uframe for idle */
		start_cs = (start_ss + 2) % 8;
		last_cs = start_cs + cs_count - 1;

		if (last_cs > 7)
			return -ERANGE;

		if (sch_ep->ep_type == ISOC_IN_EP)
			extra_cs_count = (last_cs == 7) ? 1 : 2;
		else /*  ep_type : INTR IN / INTR OUT */
			extra_cs_count = (fs_budget_start == 6) ? 1 : 2;

		cs_count += extra_cs_count;
		if (cs_count > 7)
			cs_count = 7; /* HW limit */

		for (i = 0; i < cs_count + 2; i++) {
			if (test_bit(offset + i, tt->split_bit_map))
				return -ERANGE;
		}

		sch_ep->cs_count = cs_count;
		/* one for ss, the other for idle */
		sch_ep->num_budget_microframes = cs_count + 2;

		/*
		 * if interval=1, maxp >752, num_budge_micoframe is larger
		 * than sch_ep->esit, will overstep boundary
		 */
		if (sch_ep->num_budget_microframes > sch_ep->esit)
			sch_ep->num_budget_microframes = sch_ep->esit;
	}

	return 0;
}