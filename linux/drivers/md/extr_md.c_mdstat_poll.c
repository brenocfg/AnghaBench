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
struct seq_file {scalar_t__ poll_event; } ;
struct file {struct seq_file* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLPRI ; 
 int EPOLLRDNORM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_event_count ; 
 int /*<<< orphan*/  md_event_waiters ; 
 scalar_t__ md_unloading ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t mdstat_poll(struct file *filp, poll_table *wait)
{
	struct seq_file *seq = filp->private_data;
	__poll_t mask;

	if (md_unloading)
		return EPOLLIN|EPOLLRDNORM|EPOLLERR|EPOLLPRI;
	poll_wait(filp, &md_event_waiters, wait);

	/* always allow read */
	mask = EPOLLIN | EPOLLRDNORM;

	if (seq->poll_event != atomic_read(&md_event_count))
		mask |= EPOLLERR | EPOLLPRI;
	return mask;
}