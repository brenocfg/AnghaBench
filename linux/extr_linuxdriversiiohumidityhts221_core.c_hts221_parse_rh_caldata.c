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
typedef  int /*<<< orphan*/  val ;
struct hts221_hw {TYPE_1__* sensors; int /*<<< orphan*/  regmap; } ;
typedef  int s32 ;
typedef  int s16 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int slope; int b_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTS221_REG_0RH_CAL_X_H ; 
 int /*<<< orphan*/  HTS221_REG_0RH_CAL_Y_H ; 
 int /*<<< orphan*/  HTS221_REG_1RH_CAL_X_H ; 
 int /*<<< orphan*/  HTS221_REG_1RH_CAL_Y_H ; 
 size_t HTS221_SENSOR_H ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int hts221_parse_rh_caldata(struct hts221_hw *hw)
{
	int err, *slope, *b_gen, data;
	s16 cal_x0, cal_x1, cal_y0, cal_y1;
	__le16 val;

	err = regmap_read(hw->regmap, HTS221_REG_0RH_CAL_Y_H, &data);
	if (err < 0)
		return err;
	cal_y0 = data;

	err = regmap_read(hw->regmap, HTS221_REG_1RH_CAL_Y_H, &data);
	if (err < 0)
		return err;
	cal_y1 = data;

	err = regmap_bulk_read(hw->regmap, HTS221_REG_0RH_CAL_X_H,
			       &val, sizeof(val));
	if (err < 0)
		return err;
	cal_x0 = le16_to_cpu(val);

	err = regmap_bulk_read(hw->regmap, HTS221_REG_1RH_CAL_X_H,
			       &val, sizeof(val));
	if (err < 0)
		return err;
	cal_x1 = le16_to_cpu(val);

	slope = &hw->sensors[HTS221_SENSOR_H].slope;
	b_gen = &hw->sensors[HTS221_SENSOR_H].b_gen;

	*slope = ((cal_y1 - cal_y0) * 8000) / (cal_x1 - cal_x0);
	*b_gen = (((s32)cal_x1 * cal_y0 - (s32)cal_x0 * cal_y1) * 1000) /
		 (cal_x1 - cal_x0);
	*b_gen *= 8;

	return 0;
}