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
typedef  enum preempt_state { ____Placeholder_preempt_state } preempt_state ;

/* Variables and functions */
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline bool try_preempt_state(struct a5xx_gpu *a5xx_gpu,
		enum preempt_state old, enum preempt_state new)
{
	enum preempt_state cur = atomic_cmpxchg(&a5xx_gpu->preempt_state,
		old, new);

	return (cur == old);
}