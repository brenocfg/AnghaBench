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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_pmc {TYPE_2__* soc; int /*<<< orphan*/  dev; } ;
struct tegra_io_pad_soc {int dpd; } ;
typedef  enum tegra_io_pad { ____Placeholder_tegra_io_pad } tegra_io_pad ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {unsigned long dpd_status; unsigned long dpd_req; unsigned long dpd2_status; unsigned long dpd2_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int ENOENT ; 
 int ENOTSUPP ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct tegra_io_pad_soc* tegra_io_pad_find (struct tegra_pmc*,int) ; 

__attribute__((used)) static int tegra_io_pad_get_dpd_register_bit(struct tegra_pmc *pmc,
					     enum tegra_io_pad id,
					     unsigned long *request,
					     unsigned long *status,
					     u32 *mask)
{
	const struct tegra_io_pad_soc *pad;

	pad = tegra_io_pad_find(pmc, id);
	if (!pad) {
		dev_err(pmc->dev, "invalid I/O pad ID %u\n", id);
		return -ENOENT;
	}

	if (pad->dpd == UINT_MAX)
		return -ENOTSUPP;

	*mask = BIT(pad->dpd % 32);

	if (pad->dpd < 32) {
		*status = pmc->soc->regs->dpd_status;
		*request = pmc->soc->regs->dpd_req;
	} else {
		*status = pmc->soc->regs->dpd2_status;
		*request = pmc->soc->regs->dpd2_req;
	}

	return 0;
}