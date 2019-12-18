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
struct lm73_data {int ctrl; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int LM73_CTRL_RES_MASK ; 
 int LM73_CTRL_RES_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct lm73_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/ * lm73_convrates ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t convrate_show(struct device *dev, struct device_attribute *da,
			     char *buf)
{
	struct lm73_data *data = dev_get_drvdata(dev);
	int res;

	res = (data->ctrl & LM73_CTRL_RES_MASK) >> LM73_CTRL_RES_SHIFT;
	return scnprintf(buf, PAGE_SIZE, "%hu\n", lm73_convrates[res]);
}