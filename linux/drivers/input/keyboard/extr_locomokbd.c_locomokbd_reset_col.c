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
 scalar_t__ LOCOMO_KSC ; 
 int /*<<< orphan*/  locomo_writel (unsigned short,scalar_t__) ; 

__attribute__((used)) static inline void locomokbd_reset_col(unsigned long membase, int col)
{
	unsigned short nbset;

	nbset = ((0xFF & ~(1 << col)) << 8) + 0xFF;
	locomo_writel(nbset, membase + LOCOMO_KSC);
}