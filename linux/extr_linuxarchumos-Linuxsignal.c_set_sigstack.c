#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* ss_sp; int ss_size; int /*<<< orphan*/  ss_flags; } ;
typedef  TYPE_1__ stack_t ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sigaltstack (TYPE_1__*,int /*<<< orphan*/ *) ; 

void set_sigstack(void *sig_stack, int size)
{
	stack_t stack = {
		.ss_flags = 0,
		.ss_sp = sig_stack,
		.ss_size = size - sizeof(void *)
	};

	if (sigaltstack(&stack, NULL) != 0)
		panic("enabling signal stack failed, errno = %d\n", errno);
}