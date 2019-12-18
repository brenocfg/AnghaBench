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
struct tegra_hsp {unsigned int num_si; unsigned int* shared_irqs; unsigned int shared_irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  HSP_INT_IE (unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_hsp*) ; 
 int /*<<< orphan*/  tegra_hsp_shared_irq ; 
 int /*<<< orphan*/  tegra_hsp_writel (struct tegra_hsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_hsp_request_shared_irq(struct tegra_hsp *hsp)
{
	unsigned int i, irq = 0;
	int err;

	for (i = 0; i < hsp->num_si; i++) {
		irq = hsp->shared_irqs[i];
		if (irq <= 0)
			continue;

		err = devm_request_irq(hsp->dev, irq, tegra_hsp_shared_irq, 0,
				       dev_name(hsp->dev), hsp);
		if (err < 0) {
			dev_err(hsp->dev, "failed to request interrupt: %d\n",
				err);
			continue;
		}

		hsp->shared_irq = i;

		/* disable all interrupts */
		tegra_hsp_writel(hsp, 0, HSP_INT_IE(hsp->shared_irq));

		dev_dbg(hsp->dev, "interrupt requested: %u\n", irq);

		break;
	}

	if (i == hsp->num_si) {
		dev_err(hsp->dev, "failed to find available interrupt\n");
		return -ENOENT;
	}

	return 0;
}