#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xhci_hcd_mtk {struct mu3h_sch_bw_info* sch_array; int /*<<< orphan*/  hcd; } ;
struct TYPE_4__ {int num_ports; } ;
struct TYPE_3__ {int num_ports; } ;
struct xhci_hcd {TYPE_2__ usb2_rhub; TYPE_1__ usb3_rhub; } ;
struct mu3h_sch_bw_info {int /*<<< orphan*/  bw_ep_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct xhci_hcd* hcd_to_xhci (int /*<<< orphan*/ ) ; 
 struct mu3h_sch_bw_info* kcalloc (int,int,int /*<<< orphan*/ ) ; 

int xhci_mtk_sch_init(struct xhci_hcd_mtk *mtk)
{
	struct xhci_hcd *xhci = hcd_to_xhci(mtk->hcd);
	struct mu3h_sch_bw_info *sch_array;
	int num_usb_bus;
	int i;

	/* ss IN and OUT are separated */
	num_usb_bus = xhci->usb3_rhub.num_ports * 2 + xhci->usb2_rhub.num_ports;

	sch_array = kcalloc(num_usb_bus, sizeof(*sch_array), GFP_KERNEL);
	if (sch_array == NULL)
		return -ENOMEM;

	for (i = 0; i < num_usb_bus; i++)
		INIT_LIST_HEAD(&sch_array[i].bw_ep_list);

	mtk->sch_array = sch_array;

	return 0;
}