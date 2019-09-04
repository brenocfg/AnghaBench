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
struct TYPE_3__ {int filter; int /*<<< orphan*/  bw_bits; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BMG160_REG_PMU_BW ; 
 TYPE_1__* bmg160_samp_freq_table ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmg160_set_filter(struct bmg160_data *data, int val)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;
	int i;

	for (i = 0; i < ARRAY_SIZE(bmg160_samp_freq_table); ++i) {
		if (bmg160_samp_freq_table[i].filter == val)
			break;
	}

	ret = regmap_write(data->regmap, BMG160_REG_PMU_BW,
			   bmg160_samp_freq_table[i].bw_bits);
	if (ret < 0) {
		dev_err(dev, "Error writing reg_pmu_bw\n");
		return ret;
	}

	return 0;
}