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
struct closure_waitlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __closure_wake_up (struct closure_waitlist*) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static inline void closure_wake_up(struct closure_waitlist *list)
{
	/* Memory barrier for the wait list */
	smp_mb();
	__closure_wake_up(list);
}