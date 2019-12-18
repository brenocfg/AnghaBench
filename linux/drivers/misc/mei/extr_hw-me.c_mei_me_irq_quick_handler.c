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
typedef  int /*<<< orphan*/  u32 ;
struct mei_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  me_intr_disable (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  me_intr_src (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_hcsr_read (struct mei_device*) ; 

irqreturn_t mei_me_irq_quick_handler(int irq, void *dev_id)
{
	struct mei_device *dev = (struct mei_device *)dev_id;
	u32 hcsr;

	hcsr = mei_hcsr_read(dev);
	if (!me_intr_src(hcsr))
		return IRQ_NONE;

	dev_dbg(dev->dev, "interrupt source 0x%08X\n", me_intr_src(hcsr));

	/* disable interrupts on device */
	me_intr_disable(dev, hcsr);
	return IRQ_WAKE_THREAD;
}