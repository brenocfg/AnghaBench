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

__attribute__((used)) static unsigned int elan_convert_res(char val)
{
	/*
	 * (value from firmware) * 10 + 790 = dpi
	 * dpi * 10 / 254 = dots/mm
	 */
	return (val * 10 + 790) * 10 / 254;
}