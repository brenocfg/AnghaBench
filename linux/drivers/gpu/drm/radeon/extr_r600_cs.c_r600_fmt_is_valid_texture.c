#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  enum radeon_family { ____Placeholder_radeon_family } radeon_family ;
struct TYPE_3__ {int min_family; scalar_t__ blockwidth; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* color_formats_table ; 

bool r600_fmt_is_valid_texture(u32 format, enum radeon_family family)
{
	if (format >= ARRAY_SIZE(color_formats_table))
		return false;

	if (family < color_formats_table[format].min_family)
		return false;

	if (color_formats_table[format].blockwidth > 0)
		return true;

	return false;
}