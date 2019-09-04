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
struct platform_device {int dummy; } ;
struct intel_msic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_msic_remove_devices (struct intel_msic*) ; 
 struct intel_msic* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int intel_msic_remove(struct platform_device *pdev)
{
	struct intel_msic *msic = platform_get_drvdata(pdev);

	intel_msic_remove_devices(msic);

	return 0;
}