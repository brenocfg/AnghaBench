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
struct kvaser_cmd_ext {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {scalar_t__ cmd_no; } ;
struct kvaser_cmd {TYPE_1__ header; } ;

/* Variables and functions */
 scalar_t__ CMD_EXTENDED ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t kvaser_usb_hydra_cmd_size(struct kvaser_cmd *cmd)
{
	size_t ret;

	if (cmd->header.cmd_no == CMD_EXTENDED)
		ret = le16_to_cpu(((struct kvaser_cmd_ext *)cmd)->len);
	else
		ret = sizeof(struct kvaser_cmd);

	return ret;
}