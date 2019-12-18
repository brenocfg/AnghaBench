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
typedef  int u8 ;
struct sdio_mmc_card {int* mp_regs; TYPE_1__* reg; } ;
struct mwifiex_adapter {int int_status; int /*<<< orphan*/  int_lock; struct sdio_mmc_card* card; } ;
struct TYPE_2__ {size_t host_int_status_reg; int /*<<< orphan*/  max_mp_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INTR ; 
 int MWIFIEX_SDIO_BYTE_MODE_MASK ; 
 int REG_PORT ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mwifiex_read_data_sync (struct mwifiex_adapter*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mwifiex_interrupt_status(struct mwifiex_adapter *adapter)
{
	struct sdio_mmc_card *card = adapter->card;
	u8 sdio_ireg;
	unsigned long flags;

	if (mwifiex_read_data_sync(adapter, card->mp_regs,
				   card->reg->max_mp_regs,
				   REG_PORT | MWIFIEX_SDIO_BYTE_MODE_MASK, 0)) {
		mwifiex_dbg(adapter, ERROR, "read mp_regs failed\n");
		return;
	}

	sdio_ireg = card->mp_regs[card->reg->host_int_status_reg];
	if (sdio_ireg) {
		/*
		 * DN_LD_HOST_INT_STATUS and/or UP_LD_HOST_INT_STATUS
		 * For SDIO new mode CMD port interrupts
		 *	DN_LD_CMD_PORT_HOST_INT_STATUS and/or
		 *	UP_LD_CMD_PORT_HOST_INT_STATUS
		 * Clear the interrupt status register
		 */
		mwifiex_dbg(adapter, INTR,
			    "int: sdio_ireg = %#x\n", sdio_ireg);
		spin_lock_irqsave(&adapter->int_lock, flags);
		adapter->int_status |= sdio_ireg;
		spin_unlock_irqrestore(&adapter->int_lock, flags);
	}
}