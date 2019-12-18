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
struct TYPE_2__ {int /*<<< orphan*/  info_pa; int /*<<< orphan*/  index; int /*<<< orphan*/  opcode; } ;
union ionic_dev_cmd {TYPE_1__ lif_init; } ;
typedef  int /*<<< orphan*/  u16 ;
struct ionic_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_CMD_LIF_INIT ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_dev_cmd_go (struct ionic_dev*,union ionic_dev_cmd*) ; 

void ionic_dev_cmd_lif_init(struct ionic_dev *idev, u16 lif_index,
			    dma_addr_t info_pa)
{
	union ionic_dev_cmd cmd = {
		.lif_init.opcode = IONIC_CMD_LIF_INIT,
		.lif_init.index = cpu_to_le16(lif_index),
		.lif_init.info_pa = cpu_to_le64(info_pa),
	};

	ionic_dev_cmd_go(idev, &cmd);
}