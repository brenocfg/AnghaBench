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
struct led_classdev {int dummy; } ;
struct gb_channel {int color; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 struct gb_channel* get_channel_from_cdev (struct led_classdev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t color_show(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct led_classdev *cdev = dev_get_drvdata(dev);
	struct gb_channel *channel = get_channel_from_cdev(cdev);

	return sprintf(buf, "0x%08x\n", channel->color);
}