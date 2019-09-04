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
 int LM3533_BL_ID_MASK ; 
 int LM3533_BL_ID_MAX ; 
 int LM3533_HVLED_ID_MAX ; 
 int /*<<< orphan*/  LM3533_REG_OUTPUT_CONF1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lm3533_update (struct lm3533*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lm3533_set_hvled_config(struct lm3533 *lm3533, u8 hvled, u8 bl)
{
	u8 val;
	u8 mask;
	int shift;
	int ret;

	if (hvled == 0 || hvled > LM3533_HVLED_ID_MAX)
		return -EINVAL;

	if (bl > LM3533_BL_ID_MAX)
		return -EINVAL;

	shift = hvled - 1;
	mask = LM3533_BL_ID_MASK << shift;
	val = bl << shift;

	ret = lm3533_update(lm3533, LM3533_REG_OUTPUT_CONF1, val, mask);
	if (ret)
		dev_err(lm3533->dev, "failed to set hvled config\n");

	return ret;
}