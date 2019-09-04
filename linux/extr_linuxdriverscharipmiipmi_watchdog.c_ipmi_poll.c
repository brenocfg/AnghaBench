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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 scalar_t__ data_to_read ; 
 int /*<<< orphan*/  ipmi_read_lock ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_q ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t ipmi_poll(struct file *file, poll_table *wait)
{
	__poll_t mask = 0;

	poll_wait(file, &read_q, wait);

	spin_lock_irq(&ipmi_read_lock);
	if (data_to_read)
		mask |= (EPOLLIN | EPOLLRDNORM);
	spin_unlock_irq(&ipmi_read_lock);

	return mask;
}