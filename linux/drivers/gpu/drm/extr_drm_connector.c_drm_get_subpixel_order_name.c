#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum subpixel_order { ____Placeholder_subpixel_order } subpixel_order ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 TYPE_1__* drm_subpixel_enum_list ; 

const char *drm_get_subpixel_order_name(enum subpixel_order order)
{
	return drm_subpixel_enum_list[order].name;
}