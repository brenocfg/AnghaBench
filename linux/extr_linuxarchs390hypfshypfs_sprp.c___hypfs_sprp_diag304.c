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

__attribute__((used)) static inline unsigned long __hypfs_sprp_diag304(void *data, unsigned long cmd)
{
	register unsigned long _data asm("2") = (unsigned long) data;
	register unsigned long _rc asm("3");
	register unsigned long _cmd asm("4") = cmd;

	asm volatile("diag %1,%2,0x304\n"
		     : "=d" (_rc) : "d" (_data), "d" (_cmd) : "memory");

	return _rc;
}