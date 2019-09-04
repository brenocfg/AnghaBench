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
struct pt_regs {int format; } ;

/* Variables and functions */

__attribute__((used)) static inline void adjustformat(struct pt_regs *regs)
{
	/*
	 * set format byte to make stack appear modulo 4, which it will
	 * be when doing the rte
	 */
	regs->format = 0x4;
}