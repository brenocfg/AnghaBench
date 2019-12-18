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
struct TYPE_4__ {scalar_t__ has_guest_code; scalar_t__ new_partition_table; int /*<<< orphan*/  config_area; scalar_t__ has_display_cfg; int /*<<< orphan*/  cmd_done; } ;
struct f34_data {TYPE_2__ v7; TYPE_1__* fn; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  F34_ERASE_WAIT_MS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int rmi_f34v7_erase_config (struct f34_data*) ; 
 int rmi_f34v7_erase_guest_code (struct f34_data*) ; 
 int rmi_f34v7_wait_for_idle (struct f34_data*,int /*<<< orphan*/ ) ; 
 int rmi_f34v7_write_command (struct f34_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v7_CMD_ERASE_UI_FIRMWARE ; 
 int /*<<< orphan*/  v7_DP_CONFIG_AREA ; 
 int /*<<< orphan*/  v7_UI_CONFIG_AREA ; 

__attribute__((used)) static int rmi_f34v7_erase_all(struct f34_data *f34)
{
	int ret;

	dev_info(&f34->fn->dev, "Erasing firmware...\n");

	init_completion(&f34->v7.cmd_done);

	ret = rmi_f34v7_write_command(f34, v7_CMD_ERASE_UI_FIRMWARE);
	if (ret < 0)
		return ret;

	ret = rmi_f34v7_wait_for_idle(f34, F34_ERASE_WAIT_MS);
	if (ret < 0)
		return ret;

	f34->v7.config_area = v7_UI_CONFIG_AREA;
	ret = rmi_f34v7_erase_config(f34);
	if (ret < 0)
		return ret;

	if (f34->v7.has_display_cfg) {
		f34->v7.config_area = v7_DP_CONFIG_AREA;
		ret = rmi_f34v7_erase_config(f34);
		if (ret < 0)
			return ret;
	}

	if (f34->v7.new_partition_table && f34->v7.has_guest_code) {
		ret = rmi_f34v7_erase_guest_code(f34);
		if (ret < 0)
			return ret;
	}

	return 0;
}