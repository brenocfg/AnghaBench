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
struct fpu {int initialized; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {struct fpu fpu; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  fpstate_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpu__save (struct fpu*) ; 
 int /*<<< orphan*/  trace_x86_fpu_activate_state (struct fpu*) ; 
 int /*<<< orphan*/  trace_x86_fpu_init_state (struct fpu*) ; 

void fpu__prepare_read(struct fpu *fpu)
{
	if (fpu == &current->thread.fpu) {
		fpu__save(fpu);
	} else {
		if (!fpu->initialized) {
			fpstate_init(&fpu->state);
			trace_x86_fpu_init_state(fpu);

			trace_x86_fpu_activate_state(fpu);
			/* Safe to do for current and for stopped child tasks: */
			fpu->initialized = 1;
		}
	}
}