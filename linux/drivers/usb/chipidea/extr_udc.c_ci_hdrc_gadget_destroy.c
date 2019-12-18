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
struct ci_hdrc {int /*<<< orphan*/  qh_pool; int /*<<< orphan*/  td_pool; int /*<<< orphan*/  gadget; int /*<<< orphan*/ * roles; } ;

/* Variables and functions */
 size_t CI_ROLE_GADGET ; 
 int /*<<< orphan*/  destroy_eps (struct ci_hdrc*) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

void ci_hdrc_gadget_destroy(struct ci_hdrc *ci)
{
	if (!ci->roles[CI_ROLE_GADGET])
		return;

	usb_del_gadget_udc(&ci->gadget);

	destroy_eps(ci);

	dma_pool_destroy(ci->td_pool);
	dma_pool_destroy(ci->qh_pool);
}