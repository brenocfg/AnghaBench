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
 int /*<<< orphan*/  cpci_thread ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int thread_finished ; 

__attribute__((used)) static void
cpci_stop_thread(void)
{
	kthread_stop(cpci_thread);
	thread_finished = 1;
}