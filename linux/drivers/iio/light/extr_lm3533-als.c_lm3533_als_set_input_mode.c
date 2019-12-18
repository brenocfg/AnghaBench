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
typedef  scalar_t__ u8 ;
struct lm3533_als {TYPE_1__* pdev; int /*<<< orphan*/  lm3533; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ LM3533_ALS_INPUT_MODE_MASK ; 
 int /*<<< orphan*/  LM3533_REG_ALS_CONF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int lm3533_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int lm3533_als_set_input_mode(struct lm3533_als *als, bool pwm_mode)
{
	u8 mask = LM3533_ALS_INPUT_MODE_MASK;
	u8 val;
	int ret;

	if (pwm_mode)
		val = mask;	/* pwm input */
	else
		val = 0;	/* analog input */

	ret = lm3533_update(als->lm3533, LM3533_REG_ALS_CONF, val, mask);
	if (ret) {
		dev_err(&als->pdev->dev, "failed to set input mode %d\n",
								pwm_mode);
		return ret;
	}

	return 0;
}