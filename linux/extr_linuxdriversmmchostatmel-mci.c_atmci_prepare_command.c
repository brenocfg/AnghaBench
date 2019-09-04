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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ bus_mode; } ;
struct mmc_host {TYPE_1__ ios; } ;
struct mmc_data {int blocks; int flags; } ;
struct mmc_command {scalar_t__ opcode; int flags; struct mmc_data* data; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMCI_CMDR_BLOCK ; 
 int /*<<< orphan*/  ATMCI_CMDR_CMDNB (scalar_t__) ; 
 int /*<<< orphan*/  ATMCI_CMDR_MAXLAT_64CYC ; 
 int /*<<< orphan*/  ATMCI_CMDR_MULTI_BLOCK ; 
 int /*<<< orphan*/  ATMCI_CMDR_OPDCMD ; 
 int /*<<< orphan*/  ATMCI_CMDR_RSPTYP_136BIT ; 
 int /*<<< orphan*/  ATMCI_CMDR_RSPTYP_48BIT ; 
 int /*<<< orphan*/  ATMCI_CMDR_SDIO_BLOCK ; 
 int /*<<< orphan*/  ATMCI_CMDR_START_XFER ; 
 int /*<<< orphan*/  ATMCI_CMDR_TRDIR_READ ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 scalar_t__ MMC_BUSMODE_OPENDRAIN ; 
 int MMC_DATA_READ ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 scalar_t__ SD_IO_RW_EXTENDED ; 

__attribute__((used)) static u32 atmci_prepare_command(struct mmc_host *mmc,
				 struct mmc_command *cmd)
{
	struct mmc_data	*data;
	u32		cmdr;

	cmd->error = -EINPROGRESS;

	cmdr = ATMCI_CMDR_CMDNB(cmd->opcode);

	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136)
			cmdr |= ATMCI_CMDR_RSPTYP_136BIT;
		else
			cmdr |= ATMCI_CMDR_RSPTYP_48BIT;
	}

	/*
	 * This should really be MAXLAT_5 for CMD2 and ACMD41, but
	 * it's too difficult to determine whether this is an ACMD or
	 * not. Better make it 64.
	 */
	cmdr |= ATMCI_CMDR_MAXLAT_64CYC;

	if (mmc->ios.bus_mode == MMC_BUSMODE_OPENDRAIN)
		cmdr |= ATMCI_CMDR_OPDCMD;

	data = cmd->data;
	if (data) {
		cmdr |= ATMCI_CMDR_START_XFER;

		if (cmd->opcode == SD_IO_RW_EXTENDED) {
			cmdr |= ATMCI_CMDR_SDIO_BLOCK;
		} else {
			if (data->blocks > 1)
				cmdr |= ATMCI_CMDR_MULTI_BLOCK;
			else
				cmdr |= ATMCI_CMDR_BLOCK;
		}

		if (data->flags & MMC_DATA_READ)
			cmdr |= ATMCI_CMDR_TRDIR_READ;
	}

	return cmdr;
}