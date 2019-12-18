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
struct sec_regulator_data {size_t id; scalar_t__ ext_control_gpiod; int /*<<< orphan*/  reg_node; } ;
struct sec_opmode_data {size_t id; size_t mode; } ;
struct s5m8767_info {int num_regulators; int /*<<< orphan*/  dev; struct sec_opmode_data* opmode; } ;
struct regulator_config {scalar_t__ ena_gpiod; } ;

/* Variables and functions */
 size_t S5M8767_BUCK9 ; 
 int S5M8767_ENCTRL_USE_GPIO ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int** s5m8767_opmode_reg ; 

__attribute__((used)) static void s5m8767_regulator_config_ext_control(struct s5m8767_info *s5m8767,
		struct sec_regulator_data *rdata,
		struct regulator_config *config)
{
	int i, mode = 0;

	if (rdata->id != S5M8767_BUCK9)
		return;

	/* Check if opmode for regulator matches S5M8767_ENCTRL_USE_GPIO */
	for (i = 0; i < s5m8767->num_regulators; i++) {
		const struct sec_opmode_data *opmode = &s5m8767->opmode[i];
		if (opmode->id == rdata->id) {
			mode = s5m8767_opmode_reg[rdata->id][opmode->mode];
			break;
		}
	}
	if (mode != S5M8767_ENCTRL_USE_GPIO) {
		dev_warn(s5m8767->dev,
				"ext-control for %pOFn: mismatched op_mode (%x), ignoring\n",
				rdata->reg_node, mode);
		return;
	}

	if (!rdata->ext_control_gpiod) {
		dev_warn(s5m8767->dev,
				"ext-control for %pOFn: GPIO not valid, ignoring\n",
			 rdata->reg_node);
		return;
	}

	config->ena_gpiod = rdata->ext_control_gpiod;
}