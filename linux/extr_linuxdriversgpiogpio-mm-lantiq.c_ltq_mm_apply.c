#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;
struct ltq_mm {TYPE_1__ mmchip; int /*<<< orphan*/  shadow; } ;

/* Variables and functions */
 int LTQ_EBU_BUSCON ; 
 int /*<<< orphan*/  LTQ_EBU_BUSCON1 ; 
 int LTQ_EBU_WP ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebu_lock ; 
 int /*<<< orphan*/  ltq_ebu_w32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ltq_mm_apply(struct ltq_mm *chip)
{
	unsigned long flags;

	spin_lock_irqsave(&ebu_lock, flags);
	ltq_ebu_w32(LTQ_EBU_BUSCON, LTQ_EBU_BUSCON1);
	__raw_writew(chip->shadow, chip->mmchip.regs);
	ltq_ebu_w32(LTQ_EBU_BUSCON | LTQ_EBU_WP, LTQ_EBU_BUSCON1);
	spin_unlock_irqrestore(&ebu_lock, flags);
}