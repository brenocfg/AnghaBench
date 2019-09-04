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
struct slic_upr {scalar_t__ type; } ;
struct slic_device {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int SLIC_ISR_UPCERR_MASK ; 
 scalar_t__ SLIC_UPR_LSTAT ; 
 int /*<<< orphan*/  kfree (struct slic_upr*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 struct slic_upr* slic_dequeue_upr (struct slic_device*) ; 
 int /*<<< orphan*/  slic_handle_link_irq (struct slic_device*) ; 
 int /*<<< orphan*/  slic_queue_upr (struct slic_device*,struct slic_upr*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void slic_handle_upr_irq(struct slic_device *sdev, u32 irqs)
{
	struct slic_upr *upr;

	/* remove upr that caused this irq (always the first entry in list) */
	upr = slic_dequeue_upr(sdev);
	if (!upr) {
		netdev_warn(sdev->netdev, "no upr found on list\n");
		return;
	}

	if (upr->type == SLIC_UPR_LSTAT) {
		if (unlikely(irqs & SLIC_ISR_UPCERR_MASK)) {
			/* try again */
			slic_queue_upr(sdev, upr);
			return;
		}
		slic_handle_link_irq(sdev);
	}
	kfree(upr);
}