#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dsi_data {int is_enabled; TYPE_1__* dss; int /*<<< orphan*/  irq; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 struct dsi_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dispc_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_runtime_suspend(struct device *dev)
{
	struct dsi_data *dsi = dev_get_drvdata(dev);

	dsi->is_enabled = false;
	/* ensure the irq handler sees the is_enabled value */
	smp_wmb();
	/* wait for current handler to finish before turning the DSI off */
	synchronize_irq(dsi->irq);

	dispc_runtime_put(dsi->dss->dispc);

	return 0;
}