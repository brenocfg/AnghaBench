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
struct insn_emulation {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_hw_mode ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void enable_insn_hw_mode(void *data)
{
	struct insn_emulation *insn = (struct insn_emulation *)data;
	if (insn->ops->set_hw_mode)
		insn->ops->set_hw_mode(true);
}