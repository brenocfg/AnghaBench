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
typedef  scalar_t__ u8 ;

/* Variables and functions */

__attribute__((used)) static unsigned int elan_convert_resolution(u8 val)
{
	/*
	 * (value from firmware) * 10 + 790 = dpi
	 *
	 * We also have to convert dpi to dots/mm (*10/254 to avoid floating
	 * point).
	 */

	return ((int)(char)val * 10 + 790) * 10 / 254;
}