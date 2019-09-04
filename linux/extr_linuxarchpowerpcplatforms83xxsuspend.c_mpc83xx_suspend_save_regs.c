#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sccr; } ;
struct TYPE_5__ {void* sccr; void* sicrh; void* sicrl; } ;
struct TYPE_4__ {int /*<<< orphan*/  sicrh; int /*<<< orphan*/  sicrl; } ;

/* Variables and functions */
 TYPE_3__* clock_regs ; 
 void* in_be32 (int /*<<< orphan*/ *) ; 
 TYPE_2__ saved_regs ; 
 TYPE_1__* syscr_regs ; 

__attribute__((used)) static void mpc83xx_suspend_save_regs(void)
{
	saved_regs.sicrl = in_be32(&syscr_regs->sicrl);
	saved_regs.sicrh = in_be32(&syscr_regs->sicrh);
	saved_regs.sccr = in_be32(&clock_regs->sccr);
}