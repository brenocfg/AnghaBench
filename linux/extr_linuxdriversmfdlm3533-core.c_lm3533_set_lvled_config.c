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
typedef  int u8 ;
struct lm3533 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int LM3533_LED_ID_MASK ; 
 int LM3533_LED_ID_MAX ; 
 int LM3533_LVLED_ID_MAX ; 
 int LM3533_REG_OUTPUT_CONF1 ; 
 int LM3533_REG_OUTPUT_CONF2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lm3533_update (struct lm3533*,int,int,int) ; 

__attribute__((used)) static int lm3533_set_lvled_config(struct lm3533 *lm3533, u8 lvled, u8 led)
{
	u8 reg;
	u8 val;
	u8 mask;
	int shift;
	int ret;

	if (lvled == 0 || lvled > LM3533_LVLED_ID_MAX)
		return -EINVAL;

	if (led > LM3533_LED_ID_MAX)
		return -EINVAL;

	if (lvled < 4) {
		reg = LM3533_REG_OUTPUT_CONF1;
		shift = 2 * lvled;
	} else {
		reg = LM3533_REG_OUTPUT_CONF2;
		shift = 2 * (lvled - 4);
	}

	mask = LM3533_LED_ID_MASK << shift;
	val = led << shift;

	ret = lm3533_update(lm3533, reg, val, mask);
	if (ret)
		dev_err(lm3533->dev, "failed to set lvled config\n");

	return ret;
}