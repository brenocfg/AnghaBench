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
struct ib_cq {int dummy; } ;
typedef  enum ib_cq_notify_flags { ____Placeholder_ib_cq_notify_flags } ib_cq_notify_flags ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 

int usnic_ib_req_notify_cq(struct ib_cq *cq,
					enum ib_cq_notify_flags flags)
{
	usnic_dbg("\n");
	return -EINVAL;
}