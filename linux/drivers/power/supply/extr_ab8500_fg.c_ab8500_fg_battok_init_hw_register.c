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
struct ab8500_fg {int /*<<< orphan*/  dev; TYPE_2__* bm; } ;
struct TYPE_4__ {TYPE_1__* fg_params; } ;
struct TYPE_3__ {int battok_falling_th_sel0; int battok_raising_th_sel1; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_BATT_OK_REG ; 
 int /*<<< orphan*/  AB8500_SYS_CTRL2_BLOCK ; 
 int BATT_OK_INCREMENT ; 
 int BATT_OK_MIN ; 
 int ab8500_fg_battok_calc (struct ab8500_fg*,int) ; 
 int abx500_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static int ab8500_fg_battok_init_hw_register(struct ab8500_fg *di)
{
	int selected;
	int sel0;
	int sel1;
	int cbp_sel0;
	int cbp_sel1;
	int ret;
	int new_val;

	sel0 = di->bm->fg_params->battok_falling_th_sel0;
	sel1 = di->bm->fg_params->battok_raising_th_sel1;

	cbp_sel0 = ab8500_fg_battok_calc(di, sel0);
	cbp_sel1 = ab8500_fg_battok_calc(di, sel1);

	selected = BATT_OK_MIN + cbp_sel0 * BATT_OK_INCREMENT;

	if (selected != sel0)
		dev_warn(di->dev, "Invalid voltage step:%d, using %d %d\n",
			sel0, selected, cbp_sel0);

	selected = BATT_OK_MIN + cbp_sel1 * BATT_OK_INCREMENT;

	if (selected != sel1)
		dev_warn(di->dev, "Invalid voltage step:%d, using %d %d\n",
			sel1, selected, cbp_sel1);

	new_val = cbp_sel0 | (cbp_sel1 << 4);

	dev_dbg(di->dev, "using: %x %d %d\n", new_val, cbp_sel0, cbp_sel1);
	ret = abx500_set_register_interruptible(di->dev, AB8500_SYS_CTRL2_BLOCK,
		AB8500_BATT_OK_REG, new_val);
	return ret;
}