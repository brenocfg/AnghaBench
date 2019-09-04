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
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGU_SYS ; 
 unsigned long ltq_ar9_sys_hz () ; 
 int ltq_cgu_r32 (int /*<<< orphan*/ ) ; 

unsigned long ltq_ar9_fpi_hz(void)
{
	unsigned long sys = ltq_ar9_sys_hz();

	if (ltq_cgu_r32(CGU_SYS) & BIT(0))
		return sys / 3;
	else
		return sys / 2;
}