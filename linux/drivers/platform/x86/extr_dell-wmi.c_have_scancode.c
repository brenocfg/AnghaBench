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
struct key_entry {scalar_t__ code; } ;

/* Variables and functions */

__attribute__((used)) static bool have_scancode(u32 scancode, const struct key_entry *keymap, int len)
{
	int i;

	for (i = 0; i < len; i++)
		if (keymap[i].code == scancode)
			return true;

	return false;
}