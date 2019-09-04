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
 int /*<<< orphan*/  arch_needs_sstep_emulation ; 
 int /*<<< orphan*/  break_helper (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cont_instead_of_sstep ; 
 int /*<<< orphan*/  eprintk (char*) ; 
 int /*<<< orphan*/  fill_get_buf (char*) ; 
 int /*<<< orphan*/  sstep_addr ; 
 int sstep_state ; 
 int /*<<< orphan*/  v2printk (char*) ; 

__attribute__((used)) static void emul_sstep_get(char *arg)
{
	if (!arch_needs_sstep_emulation) {
		if (cont_instead_of_sstep) {
			cont_instead_of_sstep = 0;
			fill_get_buf("c");
		} else {
			fill_get_buf(arg);
		}
		return;
	}
	switch (sstep_state) {
	case 0:
		v2printk("Emulate single step\n");
		/* Start by looking at the current PC */
		fill_get_buf("g");
		break;
	case 1:
		/* set breakpoint */
		break_helper("Z0", NULL, sstep_addr);
		break;
	case 2:
		/* Continue */
		fill_get_buf("c");
		break;
	case 3:
		/* Clear breakpoint */
		break_helper("z0", NULL, sstep_addr);
		break;
	default:
		eprintk("kgdbts: ERROR failed sstep get emulation\n");
	}
	sstep_state++;
}