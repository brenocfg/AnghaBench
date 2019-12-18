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
struct device {int dummy; } ;
struct bmg160_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMG160_REG_PMU_BW ; 
 int bmg160_convert_freq_to_bit (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bmg160_set_bw(struct bmg160_data *data, int val)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;
	int bw_bits;

	bw_bits = bmg160_convert_freq_to_bit(val);
	if (bw_bits < 0)
		return bw_bits;

	ret = regmap_write(data->regmap, BMG160_REG_PMU_BW, bw_bits);
	if (ret < 0) {
		dev_err(dev, "Error writing reg_pmu_bw\n");
		return ret;
	}

	return 0;
}