#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 scalar_t__ in_interrupt () ; 
 scalar_t__ is_global_init (TYPE_1__*) ; 
 scalar_t__ kexec_should_crash (TYPE_1__*) ; 
 scalar_t__ panic_on_oops ; 
 scalar_t__ should_fadump_crash () ; 

bool die_will_crash(void)
{
	if (should_fadump_crash())
		return true;
	if (kexec_should_crash(current))
		return true;
	if (in_interrupt() || panic_on_oops ||
			!current->pid || is_global_init(current))
		return true;

	return false;
}