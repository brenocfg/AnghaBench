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
 int /*<<< orphan*/  LOONGSON_BOOT_BASE ; 
 scalar_t__ ioremap_nocache (int /*<<< orphan*/ ,int) ; 
 void stub1 () ; 

__attribute__((used)) static inline void loongson_reboot(void)
{
#ifndef CONFIG_CPU_JUMP_WORKAROUNDS
	((void (*)(void))ioremap_nocache(LOONGSON_BOOT_BASE, 4)) ();
#else
	void (*func)(void);

	func = (void *)ioremap_nocache(LOONGSON_BOOT_BASE, 4);

	__asm__ __volatile__(
	"	.set	noat						\n"
	"	jr	%[func]						\n"
	"	.set	at						\n"
	: /* No outputs */
	: [func] "r" (func));
#endif
}