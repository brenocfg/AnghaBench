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

__attribute__((used)) static bool is_hummingbird(void)
{
	unsigned long ver, manuf, impl;

	__asm__ __volatile__ ("rdpr %%ver, %0"
			      : "=&r" (ver));
	manuf = ((ver >> 48) & 0xffff);
	impl = ((ver >> 32) & 0xffff);

	return (manuf == 0x17 && impl == 0x13);
}