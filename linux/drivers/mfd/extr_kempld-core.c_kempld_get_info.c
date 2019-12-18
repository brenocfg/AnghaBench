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
struct kempld_platform_data {int (* get_info ) (struct kempld_device_data*) ;} ;
struct TYPE_2__ {int major; int minor; int /*<<< orphan*/  buildnr; int /*<<< orphan*/  number; int /*<<< orphan*/  version; } ;
struct kempld_device_data {TYPE_1__ info; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct kempld_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int scnprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,char,char,int /*<<< orphan*/ ) ; 
 int stub1 (struct kempld_device_data*) ; 

__attribute__((used)) static int kempld_get_info(struct kempld_device_data *pld)
{
	int ret;
	const struct kempld_platform_data *pdata = dev_get_platdata(pld->dev);
	char major, minor;

	ret = pdata->get_info(pld);
	if (ret)
		return ret;

	/* The Kontron PLD firmware version string has the following format:
	 * Pwxy.zzzz
	 *   P:    Fixed
	 *   w:    PLD number    - 1 hex digit
	 *   x:    Major version - 1 alphanumerical digit (0-9A-V)
	 *   y:    Minor version - 1 alphanumerical digit (0-9A-V)
	 *   zzzz: Build number  - 4 zero padded hex digits */

	if (pld->info.major < 10)
		major = pld->info.major + '0';
	else
		major = (pld->info.major - 10) + 'A';
	if (pld->info.minor < 10)
		minor = pld->info.minor + '0';
	else
		minor = (pld->info.minor - 10) + 'A';

	ret = scnprintf(pld->info.version, sizeof(pld->info.version),
			"P%X%c%c.%04X", pld->info.number, major, minor,
			pld->info.buildnr);
	if (ret < 0)
		return ret;

	return 0;
}