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
struct TYPE_2__ {int /*<<< orphan*/  ver; int /*<<< orphan*/  opcode; } ;
union ionic_dev_cmd {TYPE_1__ identify; } ;
typedef  int /*<<< orphan*/  u8 ;
struct ionic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_CMD_IDENTIFY ; 
 int /*<<< orphan*/  ionic_dev_cmd_go (struct ionic_dev*,union ionic_dev_cmd*) ; 

void ionic_dev_cmd_identify(struct ionic_dev *idev, u8 ver)
{
	union ionic_dev_cmd cmd = {
		.identify.opcode = IONIC_CMD_IDENTIFY,
		.identify.ver = ver,
	};

	ionic_dev_cmd_go(idev, &cmd);
}