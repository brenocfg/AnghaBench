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
 int THREAD_SIZE ; 
 int current_stack_pointer ; 

__attribute__((used)) static inline void *current_stack(void)
{
	return (void *)(current_stack_pointer & ~(THREAD_SIZE - 1));
}