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
typedef  int u8 ;
typedef  int u32 ;
struct sdio_mmc_card {int mp_rd_bitmap; int curr_rd_port; int max_ports; scalar_t__ has_control_mask; scalar_t__ supports_sdio_new_mode; struct mwifiex_sdio_card_reg* reg; } ;
struct mwifiex_sdio_card_reg {int data_port_mask; int start_rd_port; } ;
struct mwifiex_adapter {struct sdio_mmc_card* card; } ;

/* Variables and functions */
 int CTRL_PORT ; 
 int CTRL_PORT_MASK ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int mwifiex_get_rd_port(struct mwifiex_adapter *adapter, u8 *port)
{
	struct sdio_mmc_card *card = adapter->card;
	const struct mwifiex_sdio_card_reg *reg = card->reg;
	u32 rd_bitmap = card->mp_rd_bitmap;

	mwifiex_dbg(adapter, DATA,
		    "data: mp_rd_bitmap=0x%08x\n", rd_bitmap);

	if (card->supports_sdio_new_mode) {
		if (!(rd_bitmap & reg->data_port_mask))
			return -1;
	} else {
		if (!(rd_bitmap & (CTRL_PORT_MASK | reg->data_port_mask)))
			return -1;
	}

	if ((card->has_control_mask) &&
	    (card->mp_rd_bitmap & CTRL_PORT_MASK)) {
		card->mp_rd_bitmap &= (u32) (~CTRL_PORT_MASK);
		*port = CTRL_PORT;
		mwifiex_dbg(adapter, DATA,
			    "data: port=%d mp_rd_bitmap=0x%08x\n",
			    *port, card->mp_rd_bitmap);
		return 0;
	}

	if (!(card->mp_rd_bitmap & (1 << card->curr_rd_port)))
		return -1;

	/* We are now handling the SDIO data ports */
	card->mp_rd_bitmap &= (u32)(~(1 << card->curr_rd_port));
	*port = card->curr_rd_port;

	if (++card->curr_rd_port == card->max_ports)
		card->curr_rd_port = reg->start_rd_port;

	mwifiex_dbg(adapter, DATA,
		    "data: port=%d mp_rd_bitmap=0x%08x -> 0x%08x\n",
		    *port, rd_bitmap, card->mp_rd_bitmap);

	return 0;
}