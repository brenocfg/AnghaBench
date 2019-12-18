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
struct ishtp_cl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ishtp_read_list_flush (struct ishtp_cl*) ; 

int ishtp_cl_flush_queues(struct ishtp_cl *cl)
{
	if (WARN_ON(!cl || !cl->dev))
		return -EINVAL;

	ishtp_read_list_flush(cl);

	return 0;
}