#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tpci200_board {TYPE_2__* info; } ;
struct TYPE_4__ {TYPE_1__* interface_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/ * control; } ;

/* Variables and functions */
 int TPCI200_INT0_EN ; 
 int TPCI200_INT1_EN ; 
 int /*<<< orphan*/  tpci200_set_mask (struct tpci200_board*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void tpci200_enable_irq(struct tpci200_board *tpci200,
			       int islot)
{
	tpci200_set_mask(tpci200,
			&tpci200->info->interface_regs->control[islot],
			TPCI200_INT0_EN | TPCI200_INT1_EN);
}