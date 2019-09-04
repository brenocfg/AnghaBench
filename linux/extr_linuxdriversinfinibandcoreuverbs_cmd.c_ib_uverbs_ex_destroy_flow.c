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
struct ib_uverbs_file {int dummy; } ;
struct ib_uverbs_destroy_flow {int /*<<< orphan*/  flow_handle; scalar_t__ comp_mask; } ;
struct ib_udata {int inlen; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UVERBS_OBJECT_FLOW ; 
 int ib_copy_from_udata (struct ib_uverbs_destroy_flow*,struct ib_udata*,int) ; 
 int uobj_perform_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_uverbs_file*,int /*<<< orphan*/ ) ; 

int ib_uverbs_ex_destroy_flow(struct ib_uverbs_file *file,
			      struct ib_udata *ucore,
			      struct ib_udata *uhw)
{
	struct ib_uverbs_destroy_flow	cmd;
	int				ret;

	if (ucore->inlen < sizeof(cmd))
		return -EINVAL;

	ret = ib_copy_from_udata(&cmd, ucore, sizeof(cmd));
	if (ret)
		return ret;

	if (cmd.comp_mask)
		return -EINVAL;

	return uobj_perform_destroy(UVERBS_OBJECT_FLOW, cmd.flow_handle, file,
				    0);
}