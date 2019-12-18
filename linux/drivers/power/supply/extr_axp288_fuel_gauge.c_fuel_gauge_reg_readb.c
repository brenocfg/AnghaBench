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
struct axp288_fg_info {TYPE_1__* pdev; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int NR_RETRY_CNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int fuel_gauge_reg_readb(struct axp288_fg_info *info, int reg)
{
	int ret, i;
	unsigned int val;

	for (i = 0; i < NR_RETRY_CNT; i++) {
		ret = regmap_read(info->regmap, reg, &val);
		if (ret == -EBUSY)
			continue;
		else
			break;
	}

	if (ret < 0) {
		dev_err(&info->pdev->dev, "axp288 reg read err:%d\n", ret);
		return ret;
	}

	return val;
}