#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct td_node {int dma; } ;
struct TYPE_6__ {TYPE_2__* ptr; } ;
struct ci_hw_ep {scalar_t__ type; int /*<<< orphan*/  dir; int /*<<< orphan*/  num; TYPE_3__ qh; } ;
struct ci_hdrc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  token; int /*<<< orphan*/  next; } ;
struct TYPE_5__ {TYPE_1__ td; } ;

/* Variables and functions */
 int TD_STATUS_ACTIVE ; 
 int TD_STATUS_HALTED ; 
 scalar_t__ USB_ENDPOINT_XFER_CONTROL ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int hw_ep_prime (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int reprime_dtd(struct ci_hdrc *ci, struct ci_hw_ep *hwep,
					   struct td_node *node)
{
	hwep->qh.ptr->td.next = cpu_to_le32(node->dma);
	hwep->qh.ptr->td.token &=
		cpu_to_le32(~(TD_STATUS_HALTED | TD_STATUS_ACTIVE));

	return hw_ep_prime(ci, hwep->num, hwep->dir,
				hwep->type == USB_ENDPOINT_XFER_CONTROL);
}