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
typedef  scalar_t__ u16 ;
struct gb_camera_fmt_info {scalar_t__ gb_format; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct gb_camera_fmt_info const*) ; 
 struct gb_camera_fmt_info const* gb_fmt_info ; 

__attribute__((used)) static const struct gb_camera_fmt_info *gb_camera_get_format_info(u16 gb_fmt)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(gb_fmt_info); i++) {
		if (gb_fmt_info[i].gb_format == gb_fmt)
			return &gb_fmt_info[i];
	}

	return NULL;
}