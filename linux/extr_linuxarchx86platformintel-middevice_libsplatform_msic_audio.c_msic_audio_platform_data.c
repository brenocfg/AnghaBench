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

/* Variables and functions */
 int /*<<< orphan*/  INTEL_MSIC_BLOCK_AUDIO ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 void* msic_generic_platform_data (void*,int /*<<< orphan*/ ) ; 
 struct platform_device* platform_device_register_simple (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void *msic_audio_platform_data(void *info)
{
	struct platform_device *pdev;

	pdev = platform_device_register_simple("sst-platform", -1, NULL, 0);

	if (IS_ERR(pdev)) {
		pr_err("failed to create audio platform device\n");
		return NULL;
	}

	return msic_generic_platform_data(info, INTEL_MSIC_BLOCK_AUDIO);
}