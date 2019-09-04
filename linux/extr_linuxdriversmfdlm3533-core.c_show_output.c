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
typedef  int u8 ;
struct TYPE_3__ {int id; } ;
struct TYPE_4__ {TYPE_1__ output; } ;
struct lm3533_device_attribute {scalar_t__ type; TYPE_2__ u; } ;
struct lm3533 {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ LM3533_ATTR_TYPE_BACKLIGHT ; 
 int LM3533_BL_ID_MASK ; 
 int LM3533_LED_ID_MASK ; 
 int LM3533_REG_OUTPUT_CONF1 ; 
 int LM3533_REG_OUTPUT_CONF2 ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct lm3533* dev_get_drvdata (struct device*) ; 
 int lm3533_read (struct lm3533*,int,int*) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct lm3533_device_attribute* to_lm3533_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_output(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct lm3533 *lm3533 = dev_get_drvdata(dev);
	struct lm3533_device_attribute *lattr = to_lm3533_dev_attr(attr);
	int id = lattr->u.output.id;
	u8 reg;
	u8 val;
	u8 mask;
	int shift;
	int ret;

	if (lattr->type == LM3533_ATTR_TYPE_BACKLIGHT) {
		reg = LM3533_REG_OUTPUT_CONF1;
		shift = id - 1;
		mask = LM3533_BL_ID_MASK << shift;
	} else {
		if (id < 4) {
			reg = LM3533_REG_OUTPUT_CONF1;
			shift = 2 * id;
		} else {
			reg = LM3533_REG_OUTPUT_CONF2;
			shift = 2 * (id - 4);
		}
		mask = LM3533_LED_ID_MASK << shift;
	}

	ret = lm3533_read(lm3533, reg, &val);
	if (ret)
		return ret;

	val = (val & mask) >> shift;

	return scnprintf(buf, PAGE_SIZE, "%u\n", val);
}