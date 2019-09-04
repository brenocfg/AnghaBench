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
typedef  int u8 ;
struct cxd2880_tnrdmd {scalar_t__ state; } ;
typedef  enum cxd2880_tnrdmd_gpio_mode { ____Placeholder_cxd2880_tnrdmd_gpio_mode } cxd2880_tnrdmd_gpio_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CXD2880_IO_TGT_SYS ; 
 int CXD2880_TNRDMD_GPIO_MODE_EEW ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 scalar_t__ CXD2880_TNRDMD_STATE_SLEEP ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_set_and_save_reg_bits (struct cxd2880_tnrdmd*,int /*<<< orphan*/ ,int,int,int,int) ; 

int cxd2880_tnrdmd_gpio_set_cfg(struct cxd2880_tnrdmd *tnr_dmd,
				u8 id,
				u8 en,
				enum cxd2880_tnrdmd_gpio_mode mode,
				u8 open_drain, u8 invert)
{
	int ret;

	if (!tnr_dmd)
		return -EINVAL;

	if (id > 2)
		return -EINVAL;

	if (mode > CXD2880_TNRDMD_GPIO_MODE_EEW)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	ret =
	    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd, CXD2880_IO_TGT_SYS,
						 0x00, 0x40 + id, mode,
						 0x0f);
	if (ret)
		return ret;

	ret =
	    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd, CXD2880_IO_TGT_SYS,
						 0x00, 0x43,
						 open_drain ? (1 << id) : 0,
						 1 << id);
	if (ret)
		return ret;

	ret =
	    cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd, CXD2880_IO_TGT_SYS,
						 0x00, 0x44,
						 invert ? (1 << id) : 0,
						 1 << id);
	if (ret)
		return ret;

	return cxd2880_tnrdmd_set_and_save_reg_bits(tnr_dmd,
						    CXD2880_IO_TGT_SYS,
						    0x00, 0x45,
						    en ? 0 : (1 << id),
						    1 << id);
}