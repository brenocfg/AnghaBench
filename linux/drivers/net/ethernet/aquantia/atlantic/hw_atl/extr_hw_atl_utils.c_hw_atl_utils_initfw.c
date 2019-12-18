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
struct aq_hw_s {struct aq_fw_ops const* aq_fw_ops; int /*<<< orphan*/  fw_ver_actual; int /*<<< orphan*/  chip_features; } ;
struct aq_fw_ops {int (* init ) (struct aq_hw_s*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HW_ATL_FW_VER_1X ; 
 int /*<<< orphan*/  HW_ATL_FW_VER_2X ; 
 int /*<<< orphan*/  HW_ATL_FW_VER_3X ; 
 struct aq_fw_ops aq_fw_1x_ops ; 
 struct aq_fw_ops aq_fw_2x_ops ; 
 int /*<<< orphan*/  aq_pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_utils_get_fw_version (struct aq_hw_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_atl_utils_hw_chip_features_init (struct aq_hw_s*,int /*<<< orphan*/ *) ; 
 int hw_atl_utils_soft_reset (struct aq_hw_s*) ; 
 scalar_t__ hw_atl_utils_ver_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct aq_hw_s*) ; 

int hw_atl_utils_initfw(struct aq_hw_s *self, const struct aq_fw_ops **fw_ops)
{
	int err = 0;

	err = hw_atl_utils_soft_reset(self);
	if (err)
		return err;

	hw_atl_utils_hw_chip_features_init(self,
					   &self->chip_features);

	hw_atl_utils_get_fw_version(self, &self->fw_ver_actual);

	if (hw_atl_utils_ver_match(HW_ATL_FW_VER_1X,
				   self->fw_ver_actual) == 0) {
		*fw_ops = &aq_fw_1x_ops;
	} else if (hw_atl_utils_ver_match(HW_ATL_FW_VER_2X,
					  self->fw_ver_actual) == 0) {
		*fw_ops = &aq_fw_2x_ops;
	} else if (hw_atl_utils_ver_match(HW_ATL_FW_VER_3X,
					  self->fw_ver_actual) == 0) {
		*fw_ops = &aq_fw_2x_ops;
	} else {
		aq_pr_err("Bad FW version detected: %x\n",
			  self->fw_ver_actual);
		return -EOPNOTSUPP;
	}
	self->aq_fw_ops = *fw_ops;
	err = self->aq_fw_ops->init(self);
	return err;
}