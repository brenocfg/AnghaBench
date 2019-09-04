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
struct TYPE_4__ {int config_area; int /*<<< orphan*/  cmd_done; } ;
struct f34_data {TYPE_2__ v7; TYPE_1__* fn; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  F34_ERASE_WAIT_MS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int rmi_f34v7_wait_for_idle (struct f34_data*,int /*<<< orphan*/ ) ; 
 int rmi_f34v7_write_command (struct f34_data*,int /*<<< orphan*/ ) ; 
#define  v7_BL_CONFIG_AREA 130 
 int /*<<< orphan*/  v7_CMD_ERASE_BL_CONFIG ; 
 int /*<<< orphan*/  v7_CMD_ERASE_DISP_CONFIG ; 
 int /*<<< orphan*/  v7_CMD_ERASE_UI_CONFIG ; 
#define  v7_DP_CONFIG_AREA 129 
#define  v7_UI_CONFIG_AREA 128 

__attribute__((used)) static int rmi_f34v7_erase_config(struct f34_data *f34)
{
	int ret;

	dev_info(&f34->fn->dev, "Erasing config...\n");

	init_completion(&f34->v7.cmd_done);

	switch (f34->v7.config_area) {
	case v7_UI_CONFIG_AREA:
		ret = rmi_f34v7_write_command(f34, v7_CMD_ERASE_UI_CONFIG);
		if (ret < 0)
			return ret;
		break;
	case v7_DP_CONFIG_AREA:
		ret = rmi_f34v7_write_command(f34, v7_CMD_ERASE_DISP_CONFIG);
		if (ret < 0)
			return ret;
		break;
	case v7_BL_CONFIG_AREA:
		ret = rmi_f34v7_write_command(f34, v7_CMD_ERASE_BL_CONFIG);
		if (ret < 0)
			return ret;
		break;
	}

	ret = rmi_f34v7_wait_for_idle(f34, F34_ERASE_WAIT_MS);
	if (ret < 0)
		return ret;

	return 0;
}