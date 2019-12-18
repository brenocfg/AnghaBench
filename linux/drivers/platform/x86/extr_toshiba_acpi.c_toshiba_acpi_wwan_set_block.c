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
struct toshiba_acpi_dev {int /*<<< orphan*/  killswitch; } ;

/* Variables and functions */
 int toshiba_wireless_status (struct toshiba_acpi_dev*) ; 
 int toshiba_wwan_set (struct toshiba_acpi_dev*,int) ; 

__attribute__((used)) static int toshiba_acpi_wwan_set_block(void *data, bool blocked)
{
	struct toshiba_acpi_dev *dev = data;
	int ret;

	ret = toshiba_wireless_status(dev);
	if (ret)
		return ret;

	if (!dev->killswitch)
		return 0;

	return toshiba_wwan_set(dev, !blocked);
}