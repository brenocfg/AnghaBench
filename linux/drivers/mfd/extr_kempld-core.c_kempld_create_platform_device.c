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
struct kempld_platform_data {int /*<<< orphan*/  ioresource; } ;
struct dmi_system_id {struct kempld_platform_data* driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kempld_pdev ; 
 int platform_device_add (int /*<<< orphan*/ ) ; 
 int platform_device_add_data (int /*<<< orphan*/ ,struct kempld_platform_data const*,int) ; 
 int platform_device_add_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kempld_create_platform_device(const struct dmi_system_id *id)
{
	const struct kempld_platform_data *pdata = id->driver_data;
	int ret;

	kempld_pdev = platform_device_alloc("kempld", -1);
	if (!kempld_pdev)
		return -ENOMEM;

	ret = platform_device_add_data(kempld_pdev, pdata, sizeof(*pdata));
	if (ret)
		goto err;

	ret = platform_device_add_resources(kempld_pdev, pdata->ioresource, 1);
	if (ret)
		goto err;

	ret = platform_device_add(kempld_pdev);
	if (ret)
		goto err;

	return 0;
err:
	platform_device_put(kempld_pdev);
	return ret;
}