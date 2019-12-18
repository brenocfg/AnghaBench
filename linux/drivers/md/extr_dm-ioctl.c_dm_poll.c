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
struct file {struct dm_file* private_data; } ;
struct dm_file {scalar_t__ global_event_nr; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_global_event_nr ; 
 int /*<<< orphan*/  dm_global_eventq ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t dm_poll(struct file *filp, poll_table *wait)
{
	struct dm_file *priv = filp->private_data;
	__poll_t mask = 0;

	poll_wait(filp, &dm_global_eventq, wait);

	if ((int)(atomic_read(&dm_global_event_nr) - priv->global_event_nr) > 0)
		mask |= EPOLLIN;

	return mask;
}