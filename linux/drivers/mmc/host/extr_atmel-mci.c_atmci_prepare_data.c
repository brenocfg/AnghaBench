#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mmc_data {int blocks; int blksz; int flags; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; int /*<<< orphan*/  error; } ;
struct atmel_mci {int need_reset; scalar_t__ pio_offset; int /*<<< orphan*/ * data_chan; struct mmc_data* data; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMCI_DATA_ERROR_FLAGS ; 
 int /*<<< orphan*/  ATMCI_RXRDY ; 
 int /*<<< orphan*/  ATMCI_TXRDY ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int MMC_DATA_READ ; 

__attribute__((used)) static u32 atmci_prepare_data(struct atmel_mci *host, struct mmc_data *data)
{
	u32 iflags;

	data->error = -EINPROGRESS;

	host->sg = data->sg;
	host->sg_len = data->sg_len;
	host->data = data;
	host->data_chan = NULL;

	iflags = ATMCI_DATA_ERROR_FLAGS;

	/*
	 * Errata: MMC data write operation with less than 12
	 * bytes is impossible.
	 *
	 * Errata: MCI Transmit Data Register (TDR) FIFO
	 * corruption when length is not multiple of 4.
	 */
	if (data->blocks * data->blksz < 12
			|| (data->blocks * data->blksz) & 3)
		host->need_reset = true;

	host->pio_offset = 0;
	if (data->flags & MMC_DATA_READ)
		iflags |= ATMCI_RXRDY;
	else
		iflags |= ATMCI_TXRDY;

	return iflags;
}