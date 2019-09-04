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
struct palmas_pmic_driver_data {TYPE_1__* sleep_req_info; } ;
struct palmas {int /*<<< orphan*/  dev; struct palmas_pmic_driver_data* pmic_ddata; } ;
typedef  enum palmas_external_requestor_id { ____Placeholder_palmas_external_requestor_id } palmas_external_requestor_id ;
struct TYPE_2__ {int bit_pos; scalar_t__ reg_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int PALMAS_ENABLE1_RES_ASSIGN ; 
 int PALMAS_ENABLE2_RES_ASSIGN ; 
 int PALMAS_EXTERNAL_REQSTR_ID_MAX ; 
 int PALMAS_EXT_CONTROL_ENABLE1 ; 
 int PALMAS_EXT_CONTROL_ENABLE2 ; 
 int PALMAS_EXT_CONTROL_NSLEEP ; 
 int PALMAS_EXT_REQ ; 
 int PALMAS_NSLEEP_RES_ASSIGN ; 
 int /*<<< orphan*/  PALMAS_PMU_CONTROL_BASE ; 
 int PALMAS_POWER_CTRL ; 
 int /*<<< orphan*/  PALMAS_RESOURCE_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int palmas_update_bits (struct palmas*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int palmas_ext_control_req_config(struct palmas *palmas,
	enum palmas_external_requestor_id id,  int ext_ctrl, bool enable)
{
	struct palmas_pmic_driver_data *pmic_ddata = palmas->pmic_ddata;
	int preq_mask_bit = 0;
	int reg_add = 0;
	int bit_pos, ret;

	if (!(ext_ctrl & PALMAS_EXT_REQ))
		return 0;

	if (id >= PALMAS_EXTERNAL_REQSTR_ID_MAX)
		return 0;

	if (ext_ctrl & PALMAS_EXT_CONTROL_NSLEEP) {
		reg_add = PALMAS_NSLEEP_RES_ASSIGN;
		preq_mask_bit = 0;
	} else if (ext_ctrl & PALMAS_EXT_CONTROL_ENABLE1) {
		reg_add = PALMAS_ENABLE1_RES_ASSIGN;
		preq_mask_bit = 1;
	} else if (ext_ctrl & PALMAS_EXT_CONTROL_ENABLE2) {
		reg_add = PALMAS_ENABLE2_RES_ASSIGN;
		preq_mask_bit = 2;
	}

	bit_pos = pmic_ddata->sleep_req_info[id].bit_pos;
	reg_add += pmic_ddata->sleep_req_info[id].reg_offset;
	if (enable)
		ret = palmas_update_bits(palmas, PALMAS_RESOURCE_BASE,
				reg_add, BIT(bit_pos), BIT(bit_pos));
	else
		ret = palmas_update_bits(palmas, PALMAS_RESOURCE_BASE,
				reg_add, BIT(bit_pos), 0);
	if (ret < 0) {
		dev_err(palmas->dev, "Resource reg 0x%02x update failed %d\n",
			reg_add, ret);
		return ret;
	}

	/* Unmask the PREQ */
	ret = palmas_update_bits(palmas, PALMAS_PMU_CONTROL_BASE,
			PALMAS_POWER_CTRL, BIT(preq_mask_bit), 0);
	if (ret < 0) {
		dev_err(palmas->dev, "POWER_CTRL register update failed %d\n",
			ret);
		return ret;
	}
	return ret;
}