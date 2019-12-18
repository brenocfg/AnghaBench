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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct lm3533_ctrlbank {int /*<<< orphan*/  dev; int /*<<< orphan*/  lm3533; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LM3533_MAX_CURRENT_MAX ; 
 scalar_t__ LM3533_MAX_CURRENT_MIN ; 
 scalar_t__ LM3533_MAX_CURRENT_STEP ; 
 int /*<<< orphan*/  LM3533_REG_MAX_CURRENT_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lm3533_ctrlbank_get_reg (struct lm3533_ctrlbank*,int /*<<< orphan*/ ) ; 
 int lm3533_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int lm3533_ctrlbank_set_max_current(struct lm3533_ctrlbank *cb, u16 imax)
{
	u8 reg;
	u8 val;
	int ret;

	if (imax < LM3533_MAX_CURRENT_MIN || imax > LM3533_MAX_CURRENT_MAX)
		return -EINVAL;

	val = (imax - LM3533_MAX_CURRENT_MIN) / LM3533_MAX_CURRENT_STEP;

	reg = lm3533_ctrlbank_get_reg(cb, LM3533_REG_MAX_CURRENT_BASE);
	ret = lm3533_write(cb->lm3533, reg, val);
	if (ret)
		dev_err(cb->dev, "failed to set max current\n");

	return ret;
}