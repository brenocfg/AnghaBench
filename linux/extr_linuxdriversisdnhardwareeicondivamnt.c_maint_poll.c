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
struct file {scalar_t__ private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 scalar_t__ diva_dbg_q_length () ; 
 int /*<<< orphan*/  msgwaitq ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t maint_poll(struct file *file, poll_table *wait)
{
	__poll_t mask = 0;

	poll_wait(file, &msgwaitq, wait);
	mask = EPOLLOUT | EPOLLWRNORM;
	if (file->private_data || diva_dbg_q_length()) {
		mask |= EPOLLIN | EPOLLRDNORM;
	}
	return (mask);
}