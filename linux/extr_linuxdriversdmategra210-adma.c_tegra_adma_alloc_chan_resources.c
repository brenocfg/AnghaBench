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
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;
struct tegra_adma_chan {TYPE_1__ vc; int /*<<< orphan*/  irq; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_chan_name (struct dma_chan*) ; 
 int /*<<< orphan*/  dma_cookie_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct tegra_adma_chan*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_adma_chan*) ; 
 int /*<<< orphan*/  tdc2dev (struct tegra_adma_chan*) ; 
 int /*<<< orphan*/  tegra_adma_isr ; 
 struct tegra_adma_chan* to_tegra_adma_chan (struct dma_chan*) ; 

__attribute__((used)) static int tegra_adma_alloc_chan_resources(struct dma_chan *dc)
{
	struct tegra_adma_chan *tdc = to_tegra_adma_chan(dc);
	int ret;

	ret = request_irq(tdc->irq, tegra_adma_isr, 0, dma_chan_name(dc), tdc);
	if (ret) {
		dev_err(tdc2dev(tdc), "failed to get interrupt for %s\n",
			dma_chan_name(dc));
		return ret;
	}

	ret = pm_runtime_get_sync(tdc2dev(tdc));
	if (ret < 0) {
		free_irq(tdc->irq, tdc);
		return ret;
	}

	dma_cookie_init(&tdc->vc.chan);

	return 0;
}