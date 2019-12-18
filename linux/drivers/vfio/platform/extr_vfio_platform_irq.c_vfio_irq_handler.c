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
struct vfio_platform_irq {int /*<<< orphan*/  trigger; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  eventfd_signal (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t vfio_irq_handler(int irq, void *dev_id)
{
	struct vfio_platform_irq *irq_ctx = dev_id;

	eventfd_signal(irq_ctx->trigger, 1);

	return IRQ_HANDLED;
}