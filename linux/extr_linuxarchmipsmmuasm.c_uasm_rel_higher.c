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

__attribute__((used)) static int uasm_rel_higher(long val)
{
#ifdef CONFIG_64BIT
	return ((((val + 0x80008000L) >> 32) & 0xffff) ^ 0x8000) - 0x8000;
#else
	return 0;
#endif
}