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
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 char const** gid_type_str ; 

const char *ib_cache_gid_type_str(enum ib_gid_type gid_type)
{
	if (gid_type < ARRAY_SIZE(gid_type_str) && gid_type_str[gid_type])
		return gid_type_str[gid_type];

	return "Invalid GID type";
}