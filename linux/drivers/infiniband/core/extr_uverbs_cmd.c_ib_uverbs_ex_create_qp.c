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
struct uverbs_attr_bundle {int dummy; } ;
struct ib_uverbs_ex_create_qp {int comp_mask; scalar_t__ reserved; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int IB_UVERBS_CREATE_QP_SUP_COMP_MASK ; 
 int create_qp (struct uverbs_attr_bundle*,struct ib_uverbs_ex_create_qp*) ; 
 int uverbs_request (struct uverbs_attr_bundle*,struct ib_uverbs_ex_create_qp*,int) ; 

__attribute__((used)) static int ib_uverbs_ex_create_qp(struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_ex_create_qp cmd;
	int ret;

	ret = uverbs_request(attrs, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	if (cmd.comp_mask & ~IB_UVERBS_CREATE_QP_SUP_COMP_MASK)
		return -EINVAL;

	if (cmd.reserved)
		return -EINVAL;

	return create_qp(attrs, &cmd);
}