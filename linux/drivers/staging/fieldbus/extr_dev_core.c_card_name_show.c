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
struct fieldbus_dev {char* card_name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct fieldbus_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t card_name_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	struct fieldbus_dev *fb = dev_get_drvdata(dev);

	/*
	 * card_name was provided by child driver, could potentially be long.
	 * protect against buffer overrun.
	 */
	return snprintf(buf, PAGE_SIZE, "%s\n", fb->card_name);
}