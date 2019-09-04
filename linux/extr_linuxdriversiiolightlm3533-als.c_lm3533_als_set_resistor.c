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
 int EINVAL ; 
 scalar_t__ LM3533_ALS_RESISTOR_MAX ; 
 scalar_t__ LM3533_ALS_RESISTOR_MIN ; 
 int /*<<< orphan*/  LM3533_REG_ALS_RESISTOR_SELECT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int lm3533_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lm3533_als_set_resistor(struct lm3533_als *als, u8 val)
{
	int ret;

	if (val < LM3533_ALS_RESISTOR_MIN || val > LM3533_ALS_RESISTOR_MAX) {
		dev_err(&als->pdev->dev, "invalid resistor value\n");
		return -EINVAL;
	};

	ret = lm3533_write(als->lm3533, LM3533_REG_ALS_RESISTOR_SELECT, val);
	if (ret) {
		dev_err(&als->pdev->dev, "failed to set resistor\n");
		return ret;
	}

	return 0;
}