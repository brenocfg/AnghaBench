#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct octnic_ctrl_pkt {int dummy; } ;
struct octeon_soft_command {int wait_time; struct octeon_soft_command* callback_arg; int /*<<< orphan*/  callback; int /*<<< orphan*/  iq_no; scalar_t__ ctxptr; scalar_t__ virtrptr; } ;
struct octeon_device {int dummy; } ;
struct oct_nic_stats_resp {int status; int /*<<< orphan*/  complete; struct net_device* netdev; } ;
struct oct_nic_stats_ctrl {int status; int /*<<< orphan*/  complete; struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* txpciq; } ;
struct lio {TYPE_3__ linfo; struct octeon_device* oct_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_5__ {TYPE_1__ s; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int IQ_SEND_FAILED ; 
 int /*<<< orphan*/  OPCODE_NIC ; 
 int /*<<< orphan*/  OPCODE_NIC_PORT_STATS ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct oct_nic_stats_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ octeon_alloc_soft_command (struct octeon_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_prepare_soft_command (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int octeon_send_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octnet_nic_stats_callback ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int octnet_get_link_stats(struct net_device *netdev)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct_dev = lio->oct_dev;
	struct octeon_soft_command *sc;
	struct oct_nic_stats_ctrl *ctrl;
	struct oct_nic_stats_resp *resp;
	int retval;

	/* Alloc soft command */
	sc = (struct octeon_soft_command *)
		octeon_alloc_soft_command(oct_dev,
					  0,
					  sizeof(struct oct_nic_stats_resp),
					  sizeof(struct octnic_ctrl_pkt));

	if (!sc)
		return -ENOMEM;

	resp = (struct oct_nic_stats_resp *)sc->virtrptr;
	memset(resp, 0, sizeof(struct oct_nic_stats_resp));

	ctrl = (struct oct_nic_stats_ctrl *)sc->ctxptr;
	memset(ctrl, 0, sizeof(struct oct_nic_stats_ctrl));
	ctrl->netdev = netdev;
	init_completion(&ctrl->complete);

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct_dev, sc, OPCODE_NIC,
				    OPCODE_NIC_PORT_STATS, 0, 0, 0);

	sc->callback = octnet_nic_stats_callback;
	sc->callback_arg = sc;
	sc->wait_time = 500;	/*in milli seconds*/

	retval = octeon_send_soft_command(oct_dev, sc);
	if (retval == IQ_SEND_FAILED) {
		octeon_free_soft_command(oct_dev, sc);
		return -EINVAL;
	}

	wait_for_completion_timeout(&ctrl->complete, msecs_to_jiffies(1000));

	if (resp->status != 1) {
		octeon_free_soft_command(oct_dev, sc);

		return -EINVAL;
	}

	octeon_free_soft_command(oct_dev, sc);

	return 0;
}