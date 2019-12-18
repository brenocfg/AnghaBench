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
struct device {int dummy; } ;
struct bmg160_data {int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {unsigned int bw_bits; int odr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BMG160_REG_PMU_BW ; 
 unsigned int BMG160_REG_PMU_BW_RES ; 
 int EINVAL ; 
 int IIO_VAL_INT ; 
 TYPE_1__* bmg160_samp_freq_table ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int bmg160_get_bw(struct bmg160_data *data, int *val)
{
	struct device *dev = regmap_get_device(data->regmap);	
	int i;
	unsigned int bw_bits;
	int ret;

	ret = regmap_read(data->regmap, BMG160_REG_PMU_BW, &bw_bits);
	if (ret < 0) {
		dev_err(dev, "Error reading reg_pmu_bw\n");
		return ret;
	}

	/* Ignore the readonly reserved bit. */
	bw_bits &= ~BMG160_REG_PMU_BW_RES;

	for (i = 0; i < ARRAY_SIZE(bmg160_samp_freq_table); ++i) {
		if (bmg160_samp_freq_table[i].bw_bits == bw_bits) {
			*val = bmg160_samp_freq_table[i].odr;
			return IIO_VAL_INT;
		}
	}

	return -EINVAL;
}