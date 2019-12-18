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
struct ib_udata {int dummy; } ;
struct ib_cq_init_attr {scalar_t__ flags; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

int usnic_ib_create_cq(struct ib_cq *ibcq, const struct ib_cq_init_attr *attr,
		       struct ib_udata *udata)
{
	if (attr->flags)
		return -EINVAL;

	return 0;
}