#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_kbc {int debounce_cnt; int repeat_cnt; int use_ghost_filter; int wakeup; int num_rows_and_columns; TYPE_2__* pin_cfg; TYPE_3__* dev; TYPE_1__* hw_support; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct TYPE_5__ {int num; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int max_rows; int max_columns; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int KBC_MAX_GPIO ; 
 int /*<<< orphan*/  PIN_CFG_COL ; 
 int /*<<< orphan*/  PIN_CFG_IGNORE ; 
 int /*<<< orphan*/  PIN_CFG_ROW ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_get_property (struct device_node*,char*,int*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int of_property_read_u32_array (struct device_node*,char*,int*,int) ; 

__attribute__((used)) static int tegra_kbc_parse_dt(struct tegra_kbc *kbc)
{
	struct device_node *np = kbc->dev->of_node;
	u32 prop;
	int i;
	u32 num_rows = 0;
	u32 num_cols = 0;
	u32 cols_cfg[KBC_MAX_GPIO];
	u32 rows_cfg[KBC_MAX_GPIO];
	int proplen;
	int ret;

	if (!of_property_read_u32(np, "nvidia,debounce-delay-ms", &prop))
		kbc->debounce_cnt = prop;

	if (!of_property_read_u32(np, "nvidia,repeat-delay-ms", &prop))
		kbc->repeat_cnt = prop;

	if (of_find_property(np, "nvidia,needs-ghost-filter", NULL))
		kbc->use_ghost_filter = true;

	if (of_property_read_bool(np, "wakeup-source") ||
	    of_property_read_bool(np, "nvidia,wakeup-source")) /* legacy */
		kbc->wakeup = true;

	if (!of_get_property(np, "nvidia,kbc-row-pins", &proplen)) {
		dev_err(kbc->dev, "property nvidia,kbc-row-pins not found\n");
		return -ENOENT;
	}
	num_rows = proplen / sizeof(u32);

	if (!of_get_property(np, "nvidia,kbc-col-pins", &proplen)) {
		dev_err(kbc->dev, "property nvidia,kbc-col-pins not found\n");
		return -ENOENT;
	}
	num_cols = proplen / sizeof(u32);

	if (num_rows > kbc->hw_support->max_rows) {
		dev_err(kbc->dev,
			"Number of rows is more than supported by hardware\n");
		return -EINVAL;
	}

	if (num_cols > kbc->hw_support->max_columns) {
		dev_err(kbc->dev,
			"Number of cols is more than supported by hardware\n");
		return -EINVAL;
	}

	if (!of_get_property(np, "linux,keymap", &proplen)) {
		dev_err(kbc->dev, "property linux,keymap not found\n");
		return -ENOENT;
	}

	if (!num_rows || !num_cols || ((num_rows + num_cols) > KBC_MAX_GPIO)) {
		dev_err(kbc->dev,
			"keypad rows/columns not properly specified\n");
		return -EINVAL;
	}

	/* Set all pins as non-configured */
	for (i = 0; i < kbc->num_rows_and_columns; i++)
		kbc->pin_cfg[i].type = PIN_CFG_IGNORE;

	ret = of_property_read_u32_array(np, "nvidia,kbc-row-pins",
				rows_cfg, num_rows);
	if (ret < 0) {
		dev_err(kbc->dev, "Rows configurations are not proper\n");
		return -EINVAL;
	}

	ret = of_property_read_u32_array(np, "nvidia,kbc-col-pins",
				cols_cfg, num_cols);
	if (ret < 0) {
		dev_err(kbc->dev, "Cols configurations are not proper\n");
		return -EINVAL;
	}

	for (i = 0; i < num_rows; i++) {
		kbc->pin_cfg[rows_cfg[i]].type = PIN_CFG_ROW;
		kbc->pin_cfg[rows_cfg[i]].num = i;
	}

	for (i = 0; i < num_cols; i++) {
		kbc->pin_cfg[cols_cfg[i]].type = PIN_CFG_COL;
		kbc->pin_cfg[cols_cfg[i]].num = i;
	}

	return 0;
}