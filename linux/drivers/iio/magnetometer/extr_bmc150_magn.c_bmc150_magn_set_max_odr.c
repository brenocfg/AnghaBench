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
struct bmc150_magn_data {int max_odr; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int BMC150_MAGN_REGVAL_TO_REPXY (int) ; 
 int BMC150_MAGN_REGVAL_TO_REPZ (int) ; 
 int /*<<< orphan*/  BMC150_MAGN_REG_REP_XY ; 
 int /*<<< orphan*/  BMC150_MAGN_REG_REP_Z ; 
 int EINVAL ; 
 int bmc150_magn_get_odr (struct bmc150_magn_data*,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int bmc150_magn_set_max_odr(struct bmc150_magn_data *data, int rep_xy,
				   int rep_z, int odr)
{
	int ret, reg_val, max_odr;

	if (rep_xy <= 0) {
		ret = regmap_read(data->regmap, BMC150_MAGN_REG_REP_XY,
				  &reg_val);
		if (ret < 0)
			return ret;
		rep_xy = BMC150_MAGN_REGVAL_TO_REPXY(reg_val);
	}
	if (rep_z <= 0) {
		ret = regmap_read(data->regmap, BMC150_MAGN_REG_REP_Z,
				  &reg_val);
		if (ret < 0)
			return ret;
		rep_z = BMC150_MAGN_REGVAL_TO_REPZ(reg_val);
	}
	if (odr <= 0) {
		ret = bmc150_magn_get_odr(data, &odr);
		if (ret < 0)
			return ret;
	}
	/* the maximum selectable read-out frequency from datasheet */
	max_odr = 1000000 / (145 * rep_xy + 500 * rep_z + 980);
	if (odr > max_odr) {
		dev_err(data->dev,
			"Can't set oversampling with sampling freq %d\n",
			odr);
		return -EINVAL;
	}
	data->max_odr = max_odr;

	return 0;
}