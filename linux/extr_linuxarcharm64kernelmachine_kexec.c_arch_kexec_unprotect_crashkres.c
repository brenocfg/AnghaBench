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
struct TYPE_4__ {int nr_segments; TYPE_1__* segment; } ;
struct TYPE_3__ {int memsz; int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __phys_to_virt (int /*<<< orphan*/ ) ; 
 TYPE_2__* kexec_crash_image ; 
 int /*<<< orphan*/  set_memory_valid (int /*<<< orphan*/ ,int,int) ; 

void arch_kexec_unprotect_crashkres(void)
{
	int i;

	for (i = 0; i < kexec_crash_image->nr_segments; i++)
		set_memory_valid(
			__phys_to_virt(kexec_crash_image->segment[i].mem),
			kexec_crash_image->segment[i].memsz >> PAGE_SHIFT, 1);
}