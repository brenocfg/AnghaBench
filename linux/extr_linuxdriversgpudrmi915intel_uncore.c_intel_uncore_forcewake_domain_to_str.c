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
typedef  enum forcewake_domain_id { ____Placeholder_forcewake_domain_id } forcewake_domain_id ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ FW_DOMAIN_ID_COUNT ; 
 int /*<<< orphan*/  WARN_ON (int const) ; 
 char const** forcewake_domain_names ; 

const char *
intel_uncore_forcewake_domain_to_str(const enum forcewake_domain_id id)
{
	BUILD_BUG_ON(ARRAY_SIZE(forcewake_domain_names) != FW_DOMAIN_ID_COUNT);

	if (id >= 0 && id < FW_DOMAIN_ID_COUNT)
		return forcewake_domain_names[id];

	WARN_ON(id);

	return "unknown";
}