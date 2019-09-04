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
struct c4iw_wr_wait {int ret; int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_put_wr_wait (struct c4iw_wr_wait*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void _c4iw_wake_up(struct c4iw_wr_wait *wr_waitp, int ret,
				 bool deref)
{
	wr_waitp->ret = ret;
	complete(&wr_waitp->completion);
	if (deref)
		c4iw_put_wr_wait(wr_waitp);
}