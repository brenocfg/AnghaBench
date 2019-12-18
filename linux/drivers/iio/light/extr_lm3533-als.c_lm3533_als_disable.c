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
typedef  int /*<<< orphan*/  u8 ;
struct lm3533_als {TYPE_1__* pdev; int /*<<< orphan*/  lm3533; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM3533_ALS_ENABLE_MASK ; 
 int /*<<< orphan*/  LM3533_REG_ALS_CONF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int lm3533_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3533_als_disable(struct lm3533_als *als)
{
	u8 mask = LM3533_ALS_ENABLE_MASK;
	int ret;

	ret = lm3533_update(als->lm3533, LM3533_REG_ALS_CONF, 0, mask);
	if (ret)
		dev_err(&als->pdev->dev, "failed to disable ALS\n");

	return ret;
}