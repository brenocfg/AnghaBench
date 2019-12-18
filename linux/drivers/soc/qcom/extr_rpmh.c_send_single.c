#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct rpmh_ctrlr {int dummy; } ;
struct device {int dummy; } ;
typedef  enum rpmh_state { ____Placeholder_rpmh_state } rpmh_state ;
struct TYPE_6__ {int wait_for_compl; int num_cmds; } ;
struct TYPE_7__ {TYPE_2__ msg; TYPE_1__* cmd; } ;
struct TYPE_5__ {void* data; void* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_RPMH_MSG_ONSTACK (struct device const*,int,int /*<<< orphan*/ *,TYPE_3__) ; 
 int RPMH_WAKE_ONLY_STATE ; 
 int /*<<< orphan*/  ctrlr_to_drv (struct rpmh_ctrlr*) ; 
 struct rpmh_ctrlr* get_rpmh_ctrlr (struct device const*) ; 
 TYPE_3__ rpm_msg ; 
 int rpmh_rsc_write_ctrl_data (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int send_single(const struct device *dev, enum rpmh_state state,
		       u32 addr, u32 data)
{
	DEFINE_RPMH_MSG_ONSTACK(dev, state, NULL, rpm_msg);
	struct rpmh_ctrlr *ctrlr = get_rpmh_ctrlr(dev);

	/* Wake sets are always complete and sleep sets are not */
	rpm_msg.msg.wait_for_compl = (state == RPMH_WAKE_ONLY_STATE);
	rpm_msg.cmd[0].addr = addr;
	rpm_msg.cmd[0].data = data;
	rpm_msg.msg.num_cmds = 1;

	return rpmh_rsc_write_ctrl_data(ctrlr_to_drv(ctrlr), &rpm_msg.msg);
}