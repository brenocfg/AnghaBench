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
 int /*<<< orphan*/  initial_thread_cb_skas (void (*) (void*),void*) ; 
 int kmalloc_ok ; 

void initial_thread_cb(void (*proc)(void *), void *arg)
{
	int save_kmalloc_ok = kmalloc_ok;

	kmalloc_ok = 0;
	initial_thread_cb_skas(proc, arg);
	kmalloc_ok = save_kmalloc_ok;
}