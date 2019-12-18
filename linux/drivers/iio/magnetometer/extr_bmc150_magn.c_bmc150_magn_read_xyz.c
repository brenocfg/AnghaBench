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
typedef  int /*<<< orphan*/  values ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  tregs ;
struct bmc150_magn_trim_regs {int dummy; } ;
struct bmc150_magn_data {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int s16 ;
typedef  struct bmc150_magn_trim_regs __le16 ;

/* Variables and functions */
 size_t AXIS_X ; 
 int AXIS_XYZR_MAX ; 
 size_t AXIS_Y ; 
 size_t AXIS_Z ; 
 int /*<<< orphan*/  BMC150_MAGN_REG_TRIM_START ; 
 int /*<<< orphan*/  BMC150_MAGN_REG_X_L ; 
 int BMC150_MAGN_SHIFT_RHALL_L ; 
 int BMC150_MAGN_SHIFT_XY_L ; 
 int BMC150_MAGN_SHIFT_Z_L ; 
 size_t RHALL ; 
 int /*<<< orphan*/  bmc150_magn_compensate_x (struct bmc150_magn_trim_regs*,int,int) ; 
 int /*<<< orphan*/  bmc150_magn_compensate_y (struct bmc150_magn_trim_regs*,int,int) ; 
 int /*<<< orphan*/  bmc150_magn_compensate_z (struct bmc150_magn_trim_regs*,int,int) ; 
 int le16_to_cpu (struct bmc150_magn_trim_regs) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bmc150_magn_trim_regs*,int) ; 

__attribute__((used)) static int bmc150_magn_read_xyz(struct bmc150_magn_data *data, s32 *buffer)
{
	int ret;
	__le16 values[AXIS_XYZR_MAX];
	s16 raw_x, raw_y, raw_z;
	u16 rhall;
	struct bmc150_magn_trim_regs tregs;

	ret = regmap_bulk_read(data->regmap, BMC150_MAGN_REG_X_L,
			       values, sizeof(values));
	if (ret < 0)
		return ret;

	raw_x = (s16)le16_to_cpu(values[AXIS_X]) >> BMC150_MAGN_SHIFT_XY_L;
	raw_y = (s16)le16_to_cpu(values[AXIS_Y]) >> BMC150_MAGN_SHIFT_XY_L;
	raw_z = (s16)le16_to_cpu(values[AXIS_Z]) >> BMC150_MAGN_SHIFT_Z_L;
	rhall = le16_to_cpu(values[RHALL]) >> BMC150_MAGN_SHIFT_RHALL_L;

	ret = regmap_bulk_read(data->regmap, BMC150_MAGN_REG_TRIM_START,
			       &tregs, sizeof(tregs));
	if (ret < 0)
		return ret;

	buffer[AXIS_X] = bmc150_magn_compensate_x(&tregs, raw_x, rhall);
	buffer[AXIS_Y] = bmc150_magn_compensate_y(&tregs, raw_y, rhall);
	buffer[AXIS_Z] = bmc150_magn_compensate_z(&tregs, raw_z, rhall);

	return 0;
}