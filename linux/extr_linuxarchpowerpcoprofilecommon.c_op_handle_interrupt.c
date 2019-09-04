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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* handle_interrupt ) (struct pt_regs*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ctr ; 
 TYPE_1__* model ; 
 int /*<<< orphan*/  stub1 (struct pt_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void op_handle_interrupt(struct pt_regs *regs)
{
	model->handle_interrupt(regs, ctr);
}