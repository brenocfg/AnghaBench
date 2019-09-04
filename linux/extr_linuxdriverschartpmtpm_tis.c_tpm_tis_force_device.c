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
struct resource {int start; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct resource const*) ; 
#define  IORESOURCE_MEM 129 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int PTR_ERR (struct platform_device*) ; 
#define  TIS_MEM_LEN 128 
 int /*<<< orphan*/  force ; 
 struct platform_device* force_pdev ; 
 struct platform_device* platform_device_register_simple (char*,int,struct resource const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpm_tis_force_device(void)
{
	struct platform_device *pdev;
	static const struct resource x86_resources[] = {
		{
			.start = 0xFED40000,
			.end = 0xFED40000 + TIS_MEM_LEN - 1,
			.flags = IORESOURCE_MEM,
		},
	};

	if (!force)
		return 0;

	/* The driver core will match the name tpm_tis of the device to
	 * the tpm_tis platform driver and complete the setup via
	 * tpm_tis_plat_probe
	 */
	pdev = platform_device_register_simple("tpm_tis", -1, x86_resources,
					       ARRAY_SIZE(x86_resources));
	if (IS_ERR(pdev))
		return PTR_ERR(pdev);
	force_pdev = pdev;

	return 0;
}