#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hwspinlock {TYPE_1__* bank; } ;
struct TYPE_2__ {int base_id; struct hwspinlock* lock; } ;

/* Variables and functions */

__attribute__((used)) static inline int hwlock_to_id(struct hwspinlock *hwlock)
{
	int local_id = hwlock - &hwlock->bank->lock[0];

	return hwlock->bank->base_id + local_id;
}