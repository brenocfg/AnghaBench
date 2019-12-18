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
typedef  scalar_t__ u32 ;
struct sh_mobile_lcdc_format_info {scalar_t__ fourcc; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct sh_mobile_lcdc_format_info const*) ; 
 struct sh_mobile_lcdc_format_info const* sh_mobile_format_infos ; 

__attribute__((used)) static const struct sh_mobile_lcdc_format_info *
sh_mobile_format_info(u32 fourcc)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(sh_mobile_format_infos); ++i) {
		if (sh_mobile_format_infos[i].fourcc == fourcc)
			return &sh_mobile_format_infos[i];
	}

	return NULL;
}