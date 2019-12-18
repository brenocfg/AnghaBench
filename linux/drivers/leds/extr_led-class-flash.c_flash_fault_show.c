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
typedef  int u32 ;
struct led_classdev_flash {int dummy; } ;
struct led_classdev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int LED_NUM_FLASH_FAULTS ; 
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 struct led_classdev_flash* lcdev_to_flcdev (struct led_classdev*) ; 
 char** led_flash_fault_names ; 
 int led_get_flash_fault (struct led_classdev_flash*,int*) ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t flash_fault_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);
	u32 fault, mask = 0x1;
	char *pbuf = buf;
	int i, ret, buf_len;

	ret = led_get_flash_fault(fled_cdev, &fault);
	if (ret < 0)
		return -EINVAL;

	*buf = '\0';

	for (i = 0; i < LED_NUM_FLASH_FAULTS; ++i) {
		if (fault & mask) {
			buf_len = sprintf(pbuf, "%s ",
					  led_flash_fault_names[i]);
			pbuf += buf_len;
		}
		mask <<= 1;
	}

	return sprintf(buf, "%s\n", buf);
}