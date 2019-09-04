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
typedef  enum source_format_class { ____Placeholder_source_format_class } source_format_class ;

/* Variables and functions */
 int dm_420_10 ; 
 int dm_420_8 ; 

__attribute__((used)) static bool is_dual_plane(enum source_format_class source_format)
{
	bool ret_val = 0;

	if ((source_format == dm_420_8) || (source_format == dm_420_10))
		ret_val = 1;

	return ret_val;
}