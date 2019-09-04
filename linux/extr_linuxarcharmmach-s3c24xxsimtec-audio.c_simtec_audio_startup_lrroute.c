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
 unsigned int BAST_CPLD_CTRL1_LRCDAC ; 
 unsigned int BAST_CPLD_CTRL1_LRMASK ; 
 int /*<<< orphan*/  BAST_VA_CTRL1 ; 
 unsigned int __raw_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void simtec_audio_startup_lrroute(void)
{
	unsigned int tmp;
	unsigned long flags;

	local_irq_save(flags);

	tmp = __raw_readb(BAST_VA_CTRL1);
	tmp &= ~BAST_CPLD_CTRL1_LRMASK;
	tmp |= BAST_CPLD_CTRL1_LRCDAC;
	__raw_writeb(tmp, BAST_VA_CTRL1);

	local_irq_restore(flags);
}