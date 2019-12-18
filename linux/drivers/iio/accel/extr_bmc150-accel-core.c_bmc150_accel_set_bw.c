#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bmc150_accel_data {int /*<<< orphan*/  bw_bits; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int val; int val2; int /*<<< orphan*/  bw_bits; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BMC150_ACCEL_REG_PMU_BW ; 
 int EINVAL ; 
 TYPE_1__* bmc150_accel_samp_freq_table ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmc150_accel_set_bw(struct bmc150_accel_data *data, int val,
			       int val2)
{
	int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(bmc150_accel_samp_freq_table); ++i) {
		if (bmc150_accel_samp_freq_table[i].val == val &&
		    bmc150_accel_samp_freq_table[i].val2 == val2) {
			ret = regmap_write(data->regmap,
				BMC150_ACCEL_REG_PMU_BW,
				bmc150_accel_samp_freq_table[i].bw_bits);
			if (ret < 0)
				return ret;

			data->bw_bits =
				bmc150_accel_samp_freq_table[i].bw_bits;
			return 0;
		}
	}

	return -EINVAL;
}