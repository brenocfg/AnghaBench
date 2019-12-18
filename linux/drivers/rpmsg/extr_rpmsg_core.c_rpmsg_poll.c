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
struct rpmsg_endpoint {TYPE_1__* ops; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* poll ) (struct rpmsg_endpoint*,struct file*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct rpmsg_endpoint*,struct file*,int /*<<< orphan*/ *) ; 

__poll_t rpmsg_poll(struct rpmsg_endpoint *ept, struct file *filp,
			poll_table *wait)
{
	if (WARN_ON(!ept))
		return 0;
	if (!ept->ops->poll)
		return 0;

	return ept->ops->poll(ept, filp, wait);
}