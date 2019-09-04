#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct pt_regs {TYPE_1__ psw; int /*<<< orphan*/  int_code; } ;
struct arch_uprobe {int /*<<< orphan*/  saved_int_code; } ;
struct TYPE_7__ {int /*<<< orphan*/  address; } ;
struct TYPE_8__ {TYPE_2__ per_event; } ;
struct TYPE_10__ {TYPE_4__* utask; TYPE_3__ thread; } ;
struct TYPE_9__ {int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_UPROBE_SINGLESTEP ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 TYPE_5__* current ; 

void arch_uprobe_abort_xol(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	clear_thread_flag(TIF_UPROBE_SINGLESTEP);
	regs->int_code = auprobe->saved_int_code;
	regs->psw.addr = current->utask->vaddr;
	current->thread.per_event.address = current->utask->vaddr;
}