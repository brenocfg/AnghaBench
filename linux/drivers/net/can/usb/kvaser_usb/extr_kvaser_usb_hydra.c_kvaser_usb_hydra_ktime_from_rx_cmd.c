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
typedef  int u64 ;
struct kvaser_usb_dev_cfg {int /*<<< orphan*/  timestamp_freq; } ;
struct TYPE_4__ {int /*<<< orphan*/  timestamp; } ;
struct kvaser_cmd_ext {TYPE_1__ rx_can; } ;
struct TYPE_5__ {int /*<<< orphan*/ * timestamp; } ;
struct TYPE_6__ {scalar_t__ cmd_no; } ;
struct kvaser_cmd {TYPE_2__ rx_can; TYPE_3__ header; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ CMD_EXTENDED ; 
 int /*<<< orphan*/  div_u64 (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ktime_t
kvaser_usb_hydra_ktime_from_rx_cmd(const struct kvaser_usb_dev_cfg *cfg,
				   const struct kvaser_cmd *cmd)
{
	u64 ticks;

	if (cmd->header.cmd_no == CMD_EXTENDED) {
		struct kvaser_cmd_ext *cmd_ext = (struct kvaser_cmd_ext *)cmd;

		ticks = le64_to_cpu(cmd_ext->rx_can.timestamp);
	} else {
		ticks = le16_to_cpu(cmd->rx_can.timestamp[0]);
		ticks += (u64)(le16_to_cpu(cmd->rx_can.timestamp[1])) << 16;
		ticks += (u64)(le16_to_cpu(cmd->rx_can.timestamp[2])) << 32;
	}

	return ns_to_ktime(div_u64(ticks * 1000, cfg->timestamp_freq));
}