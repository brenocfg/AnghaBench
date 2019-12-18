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
 int /*<<< orphan*/  B1_INSTAT ; 
 int /*<<< orphan*/  B1_OUTSTAT ; 
 int /*<<< orphan*/  T1_IRQMASTER ; 
 int /*<<< orphan*/  T1_RESETBOARD ; 
 int /*<<< orphan*/  b1_reset (unsigned int) ; 
 int /*<<< orphan*/  t1outp (unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void t1_reset(unsigned int base)
{
	/* reset T1 Controller */
	b1_reset(base);
	/* disable irq on HEMA */
	t1outp(base, B1_INSTAT, 0x00);
	t1outp(base, B1_OUTSTAT, 0x00);
	t1outp(base, T1_IRQMASTER, 0x00);
	/* reset HEMA board configuration */
	t1outp(base, T1_RESETBOARD, 0xf);
}