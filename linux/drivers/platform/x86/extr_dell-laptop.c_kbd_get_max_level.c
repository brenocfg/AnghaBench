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
struct TYPE_2__ {scalar_t__ levels; } ;

/* Variables and functions */
 TYPE_1__ kbd_info ; 
 scalar_t__ kbd_mode_levels_count ; 

__attribute__((used)) static unsigned int kbd_get_max_level(void)
{
	if (kbd_info.levels != 0)
		return kbd_info.levels;
	if (kbd_mode_levels_count > 0)
		return kbd_mode_levels_count - 1;
	return 0;
}