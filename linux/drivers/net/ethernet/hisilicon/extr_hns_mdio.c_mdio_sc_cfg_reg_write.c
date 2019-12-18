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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct hns_mdio_device {int /*<<< orphan*/  subctrl_vbase; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ MDIO_TIMEOUT ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mdio_sc_cfg_reg_write(struct hns_mdio_device *mdio_dev,
				 u32 cfg_reg, u32 set_val,
				 u32 st_reg, u32 st_msk, u8 check_st)
{
	u32 time_cnt;
	u32 reg_value;
	int ret;

	regmap_write(mdio_dev->subctrl_vbase, cfg_reg, set_val);

	for (time_cnt = MDIO_TIMEOUT; time_cnt; time_cnt--) {
		ret = regmap_read(mdio_dev->subctrl_vbase, st_reg, &reg_value);
		if (ret)
			return ret;

		reg_value &= st_msk;
		if ((!!check_st) == (!!reg_value))
			break;
	}

	if ((!!check_st) != (!!reg_value))
		return -EBUSY;

	return 0;
}