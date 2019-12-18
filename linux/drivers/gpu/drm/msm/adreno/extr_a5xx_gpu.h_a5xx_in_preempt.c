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
struct a5xx_gpu {int /*<<< orphan*/  preempt_state; } ;

/* Variables and functions */
 int PREEMPT_ABORT ; 
 int PREEMPT_NONE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool a5xx_in_preempt(struct a5xx_gpu *a5xx_gpu)
{
	int preempt_state = atomic_read(&a5xx_gpu->preempt_state);

	return !(preempt_state == PREEMPT_NONE ||
			preempt_state == PREEMPT_ABORT);
}