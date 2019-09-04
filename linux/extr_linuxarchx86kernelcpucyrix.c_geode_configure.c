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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CX86_CCR2 ; 
 int /*<<< orphan*/  CX86_CCR3 ; 
 int /*<<< orphan*/  CX86_CCR4 ; 
 int getCx86 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  setCx86 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_cx86_memwb () ; 
 int /*<<< orphan*/  set_cx86_reorder () ; 

__attribute__((used)) static void geode_configure(void)
{
	unsigned long flags;
	u8 ccr3;
	local_irq_save(flags);

	/* Suspend on halt power saving and enable #SUSP pin */
	setCx86(CX86_CCR2, getCx86(CX86_CCR2) | 0x88);

	ccr3 = getCx86(CX86_CCR3);
	setCx86(CX86_CCR3, (ccr3 & 0x0f) | 0x10);	/* enable MAPEN */


	/* FPU fast, DTE cache, Mem bypass */
	setCx86(CX86_CCR4, getCx86(CX86_CCR4) | 0x38);
	setCx86(CX86_CCR3, ccr3);			/* disable MAPEN */

	set_cx86_memwb();
	set_cx86_reorder();

	local_irq_restore(flags);
}