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
struct TYPE_2__ {scalar_t__ single_recv_buf; } ;
struct mei_me_client {int /*<<< orphan*/  tx_flow_ctrl_creds; TYPE_1__ props; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;
struct hbm_flow_control {int /*<<< orphan*/  me_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct mei_me_client* mei_me_cl_by_id (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_me_cl_put (struct mei_me_client*) ; 

__attribute__((used)) static int mei_hbm_add_single_tx_flow_ctrl_creds(struct mei_device *dev,
						 struct hbm_flow_control *fctrl)
{
	struct mei_me_client *me_cl;
	int rets;

	me_cl = mei_me_cl_by_id(dev, fctrl->me_addr);
	if (!me_cl) {
		dev_err(dev->dev, "no such me client %d\n", fctrl->me_addr);
		return -ENOENT;
	}

	if (WARN_ON(me_cl->props.single_recv_buf == 0)) {
		rets = -EINVAL;
		goto out;
	}

	me_cl->tx_flow_ctrl_creds++;
	dev_dbg(dev->dev, "recv flow ctrl msg ME %d (single) creds = %d.\n",
		fctrl->me_addr, me_cl->tx_flow_ctrl_creds);

	rets = 0;
out:
	mei_me_cl_put(me_cl);
	return rets;
}