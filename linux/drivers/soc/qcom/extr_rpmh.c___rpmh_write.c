#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; int num_cmds; int /*<<< orphan*/ * cmds; } ;
struct rpmh_request {TYPE_1__ msg; } ;
struct rpmh_ctrlr {int dummy; } ;
struct device {int dummy; } ;
struct cache_req {int dummy; } ;
typedef  enum rpmh_state { ____Placeholder_rpmh_state } rpmh_state ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct cache_req*) ; 
 int PTR_ERR (struct cache_req*) ; 
 int RPMH_ACTIVE_ONLY_STATE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct cache_req* cache_rpm_request (struct rpmh_ctrlr*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrlr_to_drv (struct rpmh_ctrlr*) ; 
 struct rpmh_ctrlr* get_rpmh_ctrlr (struct device const*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int rpmh_rsc_send_data (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rpmh_tx_done (TYPE_1__*,int) ; 

__attribute__((used)) static int __rpmh_write(const struct device *dev, enum rpmh_state state,
			struct rpmh_request *rpm_msg)
{
	struct rpmh_ctrlr *ctrlr = get_rpmh_ctrlr(dev);
	int ret = -EINVAL;
	struct cache_req *req;
	int i;

	rpm_msg->msg.state = state;

	/* Cache the request in our store and link the payload */
	for (i = 0; i < rpm_msg->msg.num_cmds; i++) {
		req = cache_rpm_request(ctrlr, state, &rpm_msg->msg.cmds[i]);
		if (IS_ERR(req))
			return PTR_ERR(req);
	}

	rpm_msg->msg.state = state;

	if (state == RPMH_ACTIVE_ONLY_STATE) {
		WARN_ON(irqs_disabled());
		ret = rpmh_rsc_send_data(ctrlr_to_drv(ctrlr), &rpm_msg->msg);
	} else {
		/* Clean up our call by spoofing tx_done */
		ret = 0;
		rpmh_tx_done(&rpm_msg->msg, ret);
	}

	return ret;
}