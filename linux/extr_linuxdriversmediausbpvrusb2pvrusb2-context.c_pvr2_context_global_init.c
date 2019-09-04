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
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pvr2_context_thread_func ; 
 int /*<<< orphan*/  pvr2_context_thread_ptr ; 

int pvr2_context_global_init(void)
{
	pvr2_context_thread_ptr = kthread_run(pvr2_context_thread_func,
					      NULL,
					      "pvrusb2-context");
	return IS_ERR(pvr2_context_thread_ptr) ? -ENOMEM : 0;
}