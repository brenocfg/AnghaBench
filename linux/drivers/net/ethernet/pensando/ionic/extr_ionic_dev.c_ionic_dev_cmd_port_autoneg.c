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
struct TYPE_2__ {int /*<<< orphan*/  an_enable; int /*<<< orphan*/  attr; int /*<<< orphan*/  index; int /*<<< orphan*/  opcode; } ;
union ionic_dev_cmd {TYPE_1__ port_setattr; } ;
typedef  int /*<<< orphan*/  u8 ;
struct ionic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_CMD_PORT_SETATTR ; 
 int /*<<< orphan*/  IONIC_PORT_ATTR_AUTONEG ; 
 int /*<<< orphan*/  ionic_dev_cmd_go (struct ionic_dev*,union ionic_dev_cmd*) ; 

void ionic_dev_cmd_port_autoneg(struct ionic_dev *idev, u8 an_enable)
{
	union ionic_dev_cmd cmd = {
		.port_setattr.opcode = IONIC_CMD_PORT_SETATTR,
		.port_setattr.index = 0,
		.port_setattr.attr = IONIC_PORT_ATTR_AUTONEG,
		.port_setattr.an_enable = an_enable,
	};

	ionic_dev_cmd_go(idev, &cmd);
}