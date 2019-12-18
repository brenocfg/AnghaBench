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
struct kvaser_usb {int dummy; } ;
struct kvaser_cmd_ext {int dummy; } ;
struct TYPE_2__ {scalar_t__ cmd_no; } ;
struct kvaser_cmd {TYPE_1__ header; } ;

/* Variables and functions */
 scalar_t__ CMD_EXTENDED ; 
 int /*<<< orphan*/  kvaser_usb_hydra_handle_cmd_ext (struct kvaser_usb const*,struct kvaser_cmd_ext*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_handle_cmd_std (struct kvaser_usb const*,struct kvaser_cmd const*) ; 

__attribute__((used)) static void kvaser_usb_hydra_handle_cmd(const struct kvaser_usb *dev,
					const struct kvaser_cmd *cmd)
{
		if (cmd->header.cmd_no == CMD_EXTENDED)
			kvaser_usb_hydra_handle_cmd_ext
					(dev, (struct kvaser_cmd_ext *)cmd);
		else
			kvaser_usb_hydra_handle_cmd_std(dev, cmd);
}