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
 int EXEC_SIZE ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 int access_process_vm (int /*<<< orphan*/ ,unsigned long,void (*) (),int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 void do_nothing () ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static void execute_user_location(void *dst)
{
	int copied;

	/* Intentionally crossing kernel/user memory boundary. */
	void (*func)(void) = dst;

	pr_info("attempting ok execution at %px\n", do_nothing);
	do_nothing();

	copied = access_process_vm(current, (unsigned long)dst, do_nothing,
				   EXEC_SIZE, FOLL_WRITE);
	if (copied < EXEC_SIZE)
		return;
	pr_info("attempting bad execution at %px\n", func);
	func();
}