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
struct preempt_client {int /*<<< orphan*/  ctx; int /*<<< orphan*/  spin; } ;

/* Variables and functions */
 int /*<<< orphan*/  igt_spinner_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_context_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void preempt_client_fini(struct preempt_client *c)
{
	igt_spinner_fini(&c->spin);
	kernel_context_close(c->ctx);
}