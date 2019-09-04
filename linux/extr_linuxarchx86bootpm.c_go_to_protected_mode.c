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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  code32_start; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 TYPE_2__ boot_params ; 
 int /*<<< orphan*/  die () ; 
 int ds () ; 
 scalar_t__ enable_a20 () ; 
 int /*<<< orphan*/  mask_all_interrupts () ; 
 int /*<<< orphan*/  protected_mode_jump (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  realmode_switch_hook () ; 
 int /*<<< orphan*/  reset_coprocessor () ; 
 int /*<<< orphan*/  setup_gdt () ; 
 int /*<<< orphan*/  setup_idt () ; 

void go_to_protected_mode(void)
{
	/* Hook before leaving real mode, also disables interrupts */
	realmode_switch_hook();

	/* Enable the A20 gate */
	if (enable_a20()) {
		puts("A20 gate not responding, unable to boot...\n");
		die();
	}

	/* Reset coprocessor (IGNNE#) */
	reset_coprocessor();

	/* Mask all interrupts in the PIC */
	mask_all_interrupts();

	/* Actual transition to protected mode... */
	setup_idt();
	setup_gdt();
	protected_mode_jump(boot_params.hdr.code32_start,
			    (u32)&boot_params + (ds() << 4));
}