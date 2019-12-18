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
typedef  int /*<<< orphan*/  u8 ;
struct ds1685_priv {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct ds1685_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1685_rtc_get_ssn (struct ds1685_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ds1685_rtc_switch_to_bank0 (struct ds1685_priv*) ; 
 int /*<<< orphan*/  ds1685_rtc_switch_to_bank1 (struct ds1685_priv*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
ds1685_rtc_sysfs_serial_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct ds1685_priv *rtc = dev_get_drvdata(dev->parent);
	u8 ssn[8];

	ds1685_rtc_switch_to_bank1(rtc);
	ds1685_rtc_get_ssn(rtc, ssn);
	ds1685_rtc_switch_to_bank0(rtc);

	return sprintf(buf, "%8phC\n", ssn);
}