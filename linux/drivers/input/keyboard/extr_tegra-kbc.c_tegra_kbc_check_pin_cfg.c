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
struct tegra_kbc_pin_cfg {int type; int /*<<< orphan*/  num; } ;
struct tegra_kbc {int /*<<< orphan*/  dev; TYPE_1__* hw_support; struct tegra_kbc_pin_cfg* pin_cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_columns; int /*<<< orphan*/  max_rows; } ;

/* Variables and functions */
 int KBC_MAX_GPIO ; 
#define  PIN_CFG_COL 130 
#define  PIN_CFG_IGNORE 129 
#define  PIN_CFG_ROW 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tegra_kbc_check_pin_cfg(const struct tegra_kbc *kbc,
					unsigned int *num_rows)
{
	int i;

	*num_rows = 0;

	for (i = 0; i < KBC_MAX_GPIO; i++) {
		const struct tegra_kbc_pin_cfg *pin_cfg = &kbc->pin_cfg[i];

		switch (pin_cfg->type) {
		case PIN_CFG_ROW:
			if (pin_cfg->num >= kbc->hw_support->max_rows) {
				dev_err(kbc->dev,
					"pin_cfg[%d]: invalid row number %d\n",
					i, pin_cfg->num);
				return false;
			}
			(*num_rows)++;
			break;

		case PIN_CFG_COL:
			if (pin_cfg->num >= kbc->hw_support->max_columns) {
				dev_err(kbc->dev,
					"pin_cfg[%d]: invalid column number %d\n",
					i, pin_cfg->num);
				return false;
			}
			break;

		case PIN_CFG_IGNORE:
			break;

		default:
			dev_err(kbc->dev,
				"pin_cfg[%d]: invalid entry type %d\n",
				pin_cfg->type, pin_cfg->num);
			return false;
		}
	}

	return true;
}