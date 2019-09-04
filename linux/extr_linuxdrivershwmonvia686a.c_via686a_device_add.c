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
struct resource {unsigned short start; char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  VIA686A_EXTENT ; 
 int acpi_check_resource_conflict (struct resource*) ; 
 int /*<<< orphan*/  pdev ; 
 int platform_device_add (int /*<<< orphan*/ ) ; 
 int platform_device_add_resources (int /*<<< orphan*/ ,struct resource*,int) ; 
 int /*<<< orphan*/  platform_device_alloc (char*,unsigned short) ; 
 int /*<<< orphan*/  platform_device_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int via686a_device_add(unsigned short address)
{
	struct resource res = {
		.start	= address,
		.end	= address + VIA686A_EXTENT - 1,
		.name	= "via686a",
		.flags	= IORESOURCE_IO,
	};
	int err;

	err = acpi_check_resource_conflict(&res);
	if (err)
		goto exit;

	pdev = platform_device_alloc("via686a", address);
	if (!pdev) {
		err = -ENOMEM;
		pr_err("Device allocation failed\n");
		goto exit;
	}

	err = platform_device_add_resources(pdev, &res, 1);
	if (err) {
		pr_err("Device resource addition failed (%d)\n", err);
		goto exit_device_put;
	}

	err = platform_device_add(pdev);
	if (err) {
		pr_err("Device addition failed (%d)\n", err);
		goto exit_device_put;
	}

	return 0;

exit_device_put:
	platform_device_put(pdev);
exit:
	return err;
}