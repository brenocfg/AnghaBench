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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ DRM_FORMAT_MOD_LINEAR ; 
 scalar_t__* sun4i_backend_formats ; 

bool sun4i_backend_format_is_supported(uint32_t fmt, uint64_t modifier)
{
	unsigned int i;

	if (modifier != DRM_FORMAT_MOD_LINEAR)
		return false;

	for (i = 0; i < ARRAY_SIZE(sun4i_backend_formats); i++)
		if (sun4i_backend_formats[i] == fmt)
			return true;

	return false;
}