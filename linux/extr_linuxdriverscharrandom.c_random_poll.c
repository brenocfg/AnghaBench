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
 scalar_t__ ENTROPY_BITS (int /*<<< orphan*/ *) ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  input_pool ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_read_wait ; 
 scalar_t__ random_read_wakeup_bits ; 
 int /*<<< orphan*/  random_write_wait ; 
 scalar_t__ random_write_wakeup_bits ; 

__attribute__((used)) static __poll_t
random_poll(struct file *file, poll_table * wait)
{
	__poll_t mask;

	poll_wait(file, &random_read_wait, wait);
	poll_wait(file, &random_write_wait, wait);
	mask = 0;
	if (ENTROPY_BITS(&input_pool) >= random_read_wakeup_bits)
		mask |= EPOLLIN | EPOLLRDNORM;
	if (ENTROPY_BITS(&input_pool) < random_write_wakeup_bits)
		mask |= EPOLLOUT | EPOLLWRNORM;
	return mask;
}