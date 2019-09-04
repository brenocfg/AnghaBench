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
 int MAP_ANONYMOUS ; 
 int MAP_PRIVATE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 unsigned long TASK_SIZE ; 
 int /*<<< orphan*/  execute_user_location (void*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 unsigned long vm_mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_munmap (unsigned long,int /*<<< orphan*/ ) ; 

void lkdtm_EXEC_USERSPACE(void)
{
	unsigned long user_addr;

	user_addr = vm_mmap(NULL, 0, PAGE_SIZE,
			    PROT_READ | PROT_WRITE | PROT_EXEC,
			    MAP_ANONYMOUS | MAP_PRIVATE, 0);
	if (user_addr >= TASK_SIZE) {
		pr_warn("Failed to allocate user memory\n");
		return;
	}
	execute_user_location((void *)user_addr);
	vm_munmap(user_addr, PAGE_SIZE);
}