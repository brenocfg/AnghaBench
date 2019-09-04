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
struct etmv4_config {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  etm4_set_default_config (struct etmv4_config*) ; 
 int /*<<< orphan*/  etm4_set_default_filter (struct etmv4_config*) ; 

__attribute__((used)) static void etm4_set_default(struct etmv4_config *config)
{
	if (WARN_ON_ONCE(!config))
		return;

	/*
	 * Make default initialisation trace everything
	 *
	 * Select the "always true" resource selector on the
	 * "Enablign Event" line and configure address range comparator
	 * '0' to trace all the possible address range.  From there
	 * configure the "include/exclude" engine to include address
	 * range comparator '0'.
	 */
	etm4_set_default_config(config);
	etm4_set_default_filter(config);
}