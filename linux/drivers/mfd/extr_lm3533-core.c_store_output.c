#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int id; } ;
struct TYPE_4__ {TYPE_1__ output; } ;
struct lm3533_device_attribute {scalar_t__ type; TYPE_2__ u; } ;
struct lm3533 {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LM3533_ATTR_TYPE_BACKLIGHT ; 
 struct lm3533* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtou8 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lm3533_set_hvled_config (struct lm3533*,int,int /*<<< orphan*/ ) ; 
 int lm3533_set_lvled_config (struct lm3533*,int,int /*<<< orphan*/ ) ; 
 struct lm3533_device_attribute* to_lm3533_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t store_output(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t len)
{
	struct lm3533 *lm3533 = dev_get_drvdata(dev);
	struct lm3533_device_attribute *lattr = to_lm3533_dev_attr(attr);
	int id = lattr->u.output.id;
	u8 val;
	int ret;

	if (kstrtou8(buf, 0, &val))
		return -EINVAL;

	if (lattr->type == LM3533_ATTR_TYPE_BACKLIGHT)
		ret = lm3533_set_hvled_config(lm3533, id, val);
	else
		ret = lm3533_set_lvled_config(lm3533, id, val);

	if (ret)
		return ret;

	return len;
}