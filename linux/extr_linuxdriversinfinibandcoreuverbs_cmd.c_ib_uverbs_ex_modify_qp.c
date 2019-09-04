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
struct ib_uverbs_file {int dummy; } ;
struct TYPE_2__ {int attr_mask; } ;
struct ib_uverbs_ex_modify_qp {TYPE_1__ base; } ;
struct ib_udata {int inlen; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IB_USER_LAST_QP_ATTR_MASK ; 
 int ib_copy_from_udata (struct ib_uverbs_ex_modify_qp*,struct ib_udata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_is_udata_cleared (struct ib_udata*,int,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int modify_qp (struct ib_uverbs_file*,struct ib_uverbs_ex_modify_qp*,struct ib_udata*) ; 

int ib_uverbs_ex_modify_qp(struct ib_uverbs_file *file,
			   struct ib_udata *ucore,
			   struct ib_udata *uhw)
{
	struct ib_uverbs_ex_modify_qp cmd = {};
	int ret;

	/*
	 * Last bit is reserved for extending the attr_mask by
	 * using another field.
	 */
	BUILD_BUG_ON(IB_USER_LAST_QP_ATTR_MASK == (1 << 31));

	if (ucore->inlen < sizeof(cmd.base))
		return -EINVAL;

	ret = ib_copy_from_udata(&cmd, ucore, min(sizeof(cmd), ucore->inlen));
	if (ret)
		return ret;

	if (cmd.base.attr_mask &
	    ~((IB_USER_LAST_QP_ATTR_MASK << 1) - 1))
		return -EOPNOTSUPP;

	if (ucore->inlen > sizeof(cmd)) {
		if (!ib_is_udata_cleared(ucore, sizeof(cmd),
					 ucore->inlen - sizeof(cmd)))
			return -EOPNOTSUPP;
	}

	ret = modify_qp(file, &cmd, uhw);

	return ret;
}