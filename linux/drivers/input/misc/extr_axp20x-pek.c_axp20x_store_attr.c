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
typedef  int /*<<< orphan*/  val_str ;
struct device {int dummy; } ;
struct axp20x_time {unsigned int idx; scalar_t__ time; } ;
struct axp20x_pek {TYPE_1__* axp20x; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_PEK_KEY ; 
 int EINVAL ; 
 unsigned int UINT_MAX ; 
 unsigned int abs (scalar_t__) ; 
 struct axp20x_pek* dev_get_drvdata (struct device*) ; 
 int ffs (unsigned int) ; 
 int kstrtouint (char*,int,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static ssize_t axp20x_store_attr(struct device *dev,
				 const struct axp20x_time *time,
				 unsigned int mask, const char *buf,
				 size_t count)
{
	struct axp20x_pek *axp20x_pek = dev_get_drvdata(dev);
	char val_str[20];
	size_t len;
	int ret, i;
	unsigned int val, idx = 0;
	unsigned int best_err = UINT_MAX;

	val_str[sizeof(val_str) - 1] = '\0';
	strncpy(val_str, buf, sizeof(val_str) - 1);
	len = strlen(val_str);

	if (len && val_str[len - 1] == '\n')
		val_str[len - 1] = '\0';

	ret = kstrtouint(val_str, 10, &val);
	if (ret)
		return ret;

	for (i = 3; i >= 0; i--) {
		unsigned int err;

		err = abs(time[i].time - val);
		if (err < best_err) {
			best_err = err;
			idx = time[i].idx;
		}

		if (!err)
			break;
	}

	idx <<= ffs(mask) - 1;
	ret = regmap_update_bits(axp20x_pek->axp20x->regmap, AXP20X_PEK_KEY,
				 mask, idx);
	if (ret != 0)
		return -EINVAL;

	return count;
}