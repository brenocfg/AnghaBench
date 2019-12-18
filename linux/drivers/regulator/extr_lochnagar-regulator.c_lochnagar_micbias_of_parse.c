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
struct regulator_desc {int id; } ;
struct regulator_config {struct lochnagar* driver_data; } ;
struct lochnagar {int /*<<< orphan*/  dev; int /*<<< orphan*/  analogue_config_lock; int /*<<< orphan*/  regmap; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCHNAGAR2_ANALOGUE_PATH_CTRL2 ; 
 int LOCHNAGAR2_P1_MICBIAS_SRC_MASK ; 
 int LOCHNAGAR2_P2_MICBIAS_SRC_SHIFT ; 
 int LOCHNAGAR_MIC1VDD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int lochnagar_micbias_of_parse(struct device_node *np,
				      const struct regulator_desc *desc,
				      struct regulator_config *config)
{
	struct lochnagar *lochnagar = config->driver_data;
	int shift = (desc->id - LOCHNAGAR_MIC1VDD) *
		    LOCHNAGAR2_P2_MICBIAS_SRC_SHIFT;
	int mask = LOCHNAGAR2_P1_MICBIAS_SRC_MASK << shift;
	unsigned int val;
	int ret;

	ret = of_property_read_u32(np, "cirrus,micbias-input", &val);
	if (ret >= 0) {
		mutex_lock(&lochnagar->analogue_config_lock);
		ret = regmap_update_bits(lochnagar->regmap,
					 LOCHNAGAR2_ANALOGUE_PATH_CTRL2,
					 mask, val << shift);
		mutex_unlock(&lochnagar->analogue_config_lock);
		if (ret < 0) {
			dev_err(lochnagar->dev,
				"Failed to update micbias source: %d\n", ret);
			return ret;
		}
	}

	return 0;
}