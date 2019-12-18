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
struct TYPE_2__ {int /*<<< orphan*/  index; int /*<<< orphan*/  opcode; } ;
union ionic_dev_cmd {TYPE_1__ port_init; } ;
struct ionic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_CMD_PORT_IDENTIFY ; 
 int /*<<< orphan*/  ionic_dev_cmd_go (struct ionic_dev*,union ionic_dev_cmd*) ; 

void ionic_dev_cmd_port_identify(struct ionic_dev *idev)
{
	union ionic_dev_cmd cmd = {
		.port_init.opcode = IONIC_CMD_PORT_IDENTIFY,
		.port_init.index = 0,
	};

	ionic_dev_cmd_go(idev, &cmd);
}