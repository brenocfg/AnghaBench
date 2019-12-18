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

/* Variables and functions */
 int ALGORITHM_RAID10_FAR ; 
 int ALGORITHM_RAID10_NEAR ; 
 int ALGORITHM_RAID10_OFFSET ; 
 int EINVAL ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static int raid10_name_to_format(const char *name)
{
	if (!strcasecmp(name, "near"))
		return ALGORITHM_RAID10_NEAR;
	else if (!strcasecmp(name, "offset"))
		return ALGORITHM_RAID10_OFFSET;
	else if (!strcasecmp(name, "far"))
		return ALGORITHM_RAID10_FAR;

	return -EINVAL;
}