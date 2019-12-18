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
typedef  int u16 ;
struct mmc_command {unsigned int flags; int opcode; TYPE_1__* data; } ;
struct cb710_mmc_reader {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CB710_MMC_CMD_AC ; 
 int CB710_MMC_CMD_ADTC ; 
 int CB710_MMC_CMD_BC ; 
 int CB710_MMC_CMD_BCR ; 
 int CB710_MMC_CMD_CODE_SHIFT ; 
 int CB710_MMC_DATA_READ ; 
 int CB710_MMC_RSP_136 ; 
 int CB710_MMC_RSP_BUSY ; 
 int CB710_MMC_RSP_NO_CRC ; 
 int CB710_MMC_RSP_PRESENT ; 
#define  MMC_CMD_AC 131 
#define  MMC_CMD_ADTC 130 
#define  MMC_CMD_BC 129 
#define  MMC_CMD_BCR 128 
 unsigned int MMC_CMD_MASK ; 
 int MMC_DATA_READ ; 
 unsigned int MMC_RSP_136 ; 
 unsigned int MMC_RSP_BUSY ; 
 unsigned int MMC_RSP_CRC ; 
 unsigned int MMC_RSP_PRESENT ; 

__attribute__((used)) static u16 cb710_encode_cmd_flags(struct cb710_mmc_reader *reader,
	struct mmc_command *cmd)
{
	unsigned int flags = cmd->flags;
	u16 cb_flags = 0;

	/* Windows driver returned 0 for commands for which no response
	 * is expected. It happened that there were only two such commands
	 * used: MMC_GO_IDLE_STATE and MMC_GO_INACTIVE_STATE so it might
	 * as well be a bug in that driver.
	 *
	 * Original driver set bit 14 for MMC/SD application
	 * commands. There's no difference 'on the wire' and
	 * it apparently works without it anyway.
	 */

	switch (flags & MMC_CMD_MASK) {
	case MMC_CMD_AC:	cb_flags = CB710_MMC_CMD_AC;	break;
	case MMC_CMD_ADTC:	cb_flags = CB710_MMC_CMD_ADTC;	break;
	case MMC_CMD_BC:	cb_flags = CB710_MMC_CMD_BC;	break;
	case MMC_CMD_BCR:	cb_flags = CB710_MMC_CMD_BCR;	break;
	}

	if (flags & MMC_RSP_BUSY)
		cb_flags |= CB710_MMC_RSP_BUSY;

	cb_flags |= cmd->opcode << CB710_MMC_CMD_CODE_SHIFT;

	if (cmd->data && (cmd->data->flags & MMC_DATA_READ))
		cb_flags |= CB710_MMC_DATA_READ;

	if (flags & MMC_RSP_PRESENT) {
		/* Windows driver set 01 at bits 4,3 except for
		 * MMC_SET_BLOCKLEN where it set 10. Maybe the
		 * hardware can do something special about this
		 * command? The original driver looks buggy/incomplete
		 * anyway so we ignore this for now.
		 *
		 * I assume that 00 here means no response is expected.
		 */
		cb_flags |= CB710_MMC_RSP_PRESENT;

		if (flags & MMC_RSP_136)
			cb_flags |= CB710_MMC_RSP_136;
		if (!(flags & MMC_RSP_CRC))
			cb_flags |= CB710_MMC_RSP_NO_CRC;
	}

	return cb_flags;
}