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
struct TYPE_5__ {int /*<<< orphan*/  sjw; int /*<<< orphan*/  phase_seg2; int /*<<< orphan*/  phase_seg1; int /*<<< orphan*/  prop_seg; int /*<<< orphan*/  sample_point; int /*<<< orphan*/  brp; int /*<<< orphan*/  tq; } ;
struct TYPE_6__ {TYPE_2__ bittiming; } ;
struct ucan_priv {TYPE_3__ can; TYPE_1__* ctl_msg_buffer; } ;
struct ucan_ctl_cmd_set_bittiming {int /*<<< orphan*/  sjw; int /*<<< orphan*/  phase_seg2; int /*<<< orphan*/  phase_seg1; int /*<<< orphan*/  prop_seg; void* sample_point; void* brp; int /*<<< orphan*/  tq; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {struct ucan_ctl_cmd_set_bittiming cmd_set_bittiming; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCAN_COMMAND_SET_BITTIMING ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct ucan_priv* netdev_priv (struct net_device*) ; 
 int ucan_ctrl_command_out (struct ucan_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ucan_set_bittiming(struct net_device *netdev)
{
	int ret;
	struct ucan_priv *up = netdev_priv(netdev);
	struct ucan_ctl_cmd_set_bittiming *cmd_set_bittiming;

	cmd_set_bittiming = &up->ctl_msg_buffer->cmd_set_bittiming;
	cmd_set_bittiming->tq = cpu_to_le32(up->can.bittiming.tq);
	cmd_set_bittiming->brp = cpu_to_le16(up->can.bittiming.brp);
	cmd_set_bittiming->sample_point =
	    cpu_to_le16(up->can.bittiming.sample_point);
	cmd_set_bittiming->prop_seg = up->can.bittiming.prop_seg;
	cmd_set_bittiming->phase_seg1 = up->can.bittiming.phase_seg1;
	cmd_set_bittiming->phase_seg2 = up->can.bittiming.phase_seg2;
	cmd_set_bittiming->sjw = up->can.bittiming.sjw;

	ret = ucan_ctrl_command_out(up, UCAN_COMMAND_SET_BITTIMING, 0,
				    sizeof(*cmd_set_bittiming));
	return (ret < 0) ? ret : 0;
}