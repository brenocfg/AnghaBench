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
struct toshiba_acpi_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int SCI_KBD_MODE_MASK ; 
 struct toshiba_acpi_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ toshiba_kbd_illum_status_get (struct toshiba_acpi_dev*,int*) ; 

__attribute__((used)) static ssize_t kbd_backlight_mode_show(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	struct toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	u32 time;

	if (toshiba_kbd_illum_status_get(toshiba, &time) < 0)
		return -EIO;

	return sprintf(buf, "%i\n", time & SCI_KBD_MODE_MASK);
}