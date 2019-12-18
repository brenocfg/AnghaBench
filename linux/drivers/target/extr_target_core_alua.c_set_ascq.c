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
typedef  int /*<<< orphan*/  u8 ;
struct se_cmd {int scsi_asc; int /*<<< orphan*/  scsi_ascq; TYPE_1__* se_tfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  fabric_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_ascq(struct se_cmd *cmd, u8 alua_ascq)
{
	/*
	 * Set SCSI additional sense code (ASC) to 'LUN Not Accessible';
	 * The ALUA additional sense code qualifier (ASCQ) is determined
	 * by the ALUA primary or secondary access state..
	 */
	pr_debug("[%s]: ALUA TG Port not available, "
		"SenseKey: NOT_READY, ASC/ASCQ: "
		"0x04/0x%02x\n",
		cmd->se_tfo->fabric_name, alua_ascq);

	cmd->scsi_asc = 0x04;
	cmd->scsi_ascq = alua_ascq;
}