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
typedef  enum intel_platform { ____Placeholder_intel_platform } intel_platform ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ INTEL_MAX_PLATFORMS ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 char const** platform_names ; 

const char *intel_platform_name(enum intel_platform platform)
{
	BUILD_BUG_ON(ARRAY_SIZE(platform_names) != INTEL_MAX_PLATFORMS);

	if (WARN_ON_ONCE(platform >= ARRAY_SIZE(platform_names) ||
			 platform_names[platform] == NULL))
		return "<unknown>";

	return platform_names[platform];
}