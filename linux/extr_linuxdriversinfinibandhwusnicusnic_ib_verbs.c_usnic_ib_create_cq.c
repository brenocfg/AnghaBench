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
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_cq_init_attr {scalar_t__ flags; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 struct ib_cq* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ib_cq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 

struct ib_cq *usnic_ib_create_cq(struct ib_device *ibdev,
				 const struct ib_cq_init_attr *attr,
				 struct ib_ucontext *context,
				 struct ib_udata *udata)
{
	struct ib_cq *cq;

	usnic_dbg("\n");
	if (attr->flags)
		return ERR_PTR(-EINVAL);

	cq = kzalloc(sizeof(*cq), GFP_KERNEL);
	if (!cq)
		return ERR_PTR(-EBUSY);

	return cq;
}