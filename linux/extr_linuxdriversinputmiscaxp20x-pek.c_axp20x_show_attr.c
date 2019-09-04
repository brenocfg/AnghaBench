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
struct device {int dummy; } ;
struct axp20x_time {unsigned int idx; unsigned int time; } ;
struct axp20x_pek {TYPE_1__* axp20x; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_PEK_KEY ; 
 struct axp20x_pek* dev_get_drvdata (struct device*) ; 
 int ffs (unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static ssize_t axp20x_show_attr(struct device *dev,
				const struct axp20x_time *time,
				unsigned int mask, char *buf)
{
	struct axp20x_pek *axp20x_pek = dev_get_drvdata(dev);
	unsigned int val;
	int ret, i;

	ret = regmap_read(axp20x_pek->axp20x->regmap, AXP20X_PEK_KEY, &val);
	if (ret != 0)
		return ret;

	val &= mask;
	val >>= ffs(mask) - 1;

	for (i = 0; i < 4; i++)
		if (val == time[i].idx)
			val = time[i].time;

	return sprintf(buf, "%u\n", val);
}