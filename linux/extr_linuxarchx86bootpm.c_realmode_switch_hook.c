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
struct TYPE_3__ {scalar_t__ realmode_swtch; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 TYPE_2__ boot_params ; 
 int /*<<< orphan*/  io_delay () ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static void realmode_switch_hook(void)
{
	if (boot_params.hdr.realmode_swtch) {
		asm volatile("lcallw *%0"
			     : : "m" (boot_params.hdr.realmode_swtch)
			     : "eax", "ebx", "ecx", "edx");
	} else {
		asm volatile("cli");
		outb(0x80, 0x70); /* Disable NMI */
		io_delay();
	}
}