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
struct venus_core {TYPE_1__* res; int /*<<< orphan*/  done; int /*<<< orphan*/  state; struct hfi_core_ops const* core_ops; int /*<<< orphan*/  insts_count; } ;
struct hfi_core_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hfi_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_UNINIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_set_version (int /*<<< orphan*/ ) ; 
 int venus_hfi_create (struct venus_core*) ; 

int hfi_create(struct venus_core *core, const struct hfi_core_ops *ops)
{
	int ret;

	if (!ops)
		return -EINVAL;

	atomic_set(&core->insts_count, 0);
	core->core_ops = ops;
	core->state = CORE_UNINIT;
	init_completion(&core->done);
	pkt_set_version(core->res->hfi_version);
	ret = venus_hfi_create(core);

	return ret;
}