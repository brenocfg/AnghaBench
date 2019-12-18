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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct axp20x_pek {TYPE_1__* info; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  startup_mask; int /*<<< orphan*/  startup_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  axp20x_show_attr (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct axp20x_pek* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static ssize_t axp20x_show_attr_startup(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct axp20x_pek *axp20x_pek = dev_get_drvdata(dev);

	return axp20x_show_attr(dev, axp20x_pek->info->startup_time,
				axp20x_pek->info->startup_mask, buf);
}