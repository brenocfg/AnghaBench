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
struct dps310_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPS310_CFG_REG ; 
 int /*<<< orphan*/  DPS310_TMP_CFG ; 
 int /*<<< orphan*/  DPS310_TMP_PRC_BITS ; 
 int /*<<< orphan*/  DPS310_TMP_SHIFT_EN ; 
 int EINVAL ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dps310_set_temp_precision(struct dps310_data *data, int val)
{
	int rc;
	u8 shift_en;

	if (val < 0 || val > 128)
		return -EINVAL;

	shift_en = val >= 16 ? DPS310_TMP_SHIFT_EN : 0;
	rc = regmap_write_bits(data->regmap, DPS310_CFG_REG,
			       DPS310_TMP_SHIFT_EN, shift_en);
	if (rc)
		return rc;

	return regmap_update_bits(data->regmap, DPS310_TMP_CFG,
				  DPS310_TMP_PRC_BITS, ilog2(val));
}