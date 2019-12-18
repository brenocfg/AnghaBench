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
struct mu3h_sch_tt {int /*<<< orphan*/  ep_list; int /*<<< orphan*/  split_bit_map; } ;
struct mu3h_sch_ep_info {int esit; int offset; int num_budget_microframes; int /*<<< orphan*/  tt_endpoint; struct mu3h_sch_tt* sch_tt; } ;

/* Variables and functions */
 int XHCI_MTK_MAX_ESIT ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_sch_tt(struct usb_device *udev,
	struct mu3h_sch_ep_info *sch_ep)
{
	struct mu3h_sch_tt *tt = sch_ep->sch_tt;
	u32 base, num_esit;
	int i, j;

	num_esit = XHCI_MTK_MAX_ESIT / sch_ep->esit;
	for (i = 0; i < num_esit; i++) {
		base = sch_ep->offset + i * sch_ep->esit;
		for (j = 0; j < sch_ep->num_budget_microframes; j++)
			set_bit(base + j, tt->split_bit_map);
	}

	list_add_tail(&sch_ep->tt_endpoint, &tt->ep_list);
}