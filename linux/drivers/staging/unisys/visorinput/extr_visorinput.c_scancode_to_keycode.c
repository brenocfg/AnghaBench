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
 int* visorkbd_ext_keycode ; 
 int* visorkbd_keycode ; 

__attribute__((used)) static int scancode_to_keycode(int scancode)
{
	if (scancode > 0xff)
		return visorkbd_ext_keycode[(scancode >> 8) & 0xff];

	return visorkbd_keycode[scancode];
}