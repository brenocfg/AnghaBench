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
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ qlcnic_83xx_get_reset_instruction_template (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_check_driver_presence_reg (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_idc_check_major_version (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_idc_first_to_load_function_handler (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_update_audit_reg (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_setup_idc_parameters (struct qlcnic_adapter*) ; 

int qlcnic_83xx_idc_init(struct qlcnic_adapter *adapter)
{
	int ret = -EIO;

	qlcnic_83xx_setup_idc_parameters(adapter);

	if (qlcnic_83xx_get_reset_instruction_template(adapter))
		return ret;

	if (!qlcnic_83xx_idc_check_driver_presence_reg(adapter)) {
		if (qlcnic_83xx_idc_first_to_load_function_handler(adapter))
			return -EIO;
	} else {
		if (qlcnic_83xx_idc_check_major_version(adapter))
			return -EIO;
	}

	qlcnic_83xx_idc_update_audit_reg(adapter, 0, 1);

	return 0;
}