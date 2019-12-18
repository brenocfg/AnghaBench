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
struct dispc_device {int is_enabled; int /*<<< orphan*/  irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct dispc_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dispc_save_context (struct dispc_device*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dispc_runtime_suspend(struct device *dev)
{
	struct dispc_device *dispc = dev_get_drvdata(dev);

	dispc->is_enabled = false;
	/* ensure the dispc_irq_handler sees the is_enabled value */
	smp_wmb();
	/* wait for current handler to finish before turning the DISPC off */
	synchronize_irq(dispc->irq);

	dispc_save_context(dispc);

	return 0;
}