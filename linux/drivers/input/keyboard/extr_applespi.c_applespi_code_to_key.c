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
typedef  size_t u8 ;

/* Variables and functions */
 unsigned int* applespi_scancodes ; 
 unsigned int applespi_translate_fn_key (unsigned int,int) ; 
 unsigned int applespi_translate_iso_layout (unsigned int) ; 
 scalar_t__ fnmode ; 
 scalar_t__ iso_layout ; 

__attribute__((used)) static unsigned int applespi_code_to_key(u8 code, int fn_pressed)
{
	unsigned int key = applespi_scancodes[code];

	if (fnmode)
		key = applespi_translate_fn_key(key, fn_pressed);
	if (iso_layout)
		key = applespi_translate_iso_layout(key);
	return key;
}