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
typedef  int u32 ;
struct sdio_mmc_card {int mp_wr_bitmap; int mp_data_port_mask; int curr_wr_port; int mp_end_port; scalar_t__ has_control_mask; struct mwifiex_sdio_card_reg* reg; } ;
struct mwifiex_sdio_card_reg {int start_wr_port; } ;
struct mwifiex_adapter {int data_sent; struct sdio_mmc_card* card; } ;

/* Variables and functions */
 int CTRL_PORT ; 
 int /*<<< orphan*/  DATA ; 
 int EBUSY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int mwifiex_get_wr_port_data(struct mwifiex_adapter *adapter, u32 *port)
{
	struct sdio_mmc_card *card = adapter->card;
	const struct mwifiex_sdio_card_reg *reg = card->reg;
	u32 wr_bitmap = card->mp_wr_bitmap;

	mwifiex_dbg(adapter, DATA,
		    "data: mp_wr_bitmap=0x%08x\n", wr_bitmap);

	if (!(wr_bitmap & card->mp_data_port_mask)) {
		adapter->data_sent = true;
		return -EBUSY;
	}

	if (card->mp_wr_bitmap & (1 << card->curr_wr_port)) {
		card->mp_wr_bitmap &= (u32) (~(1 << card->curr_wr_port));
		*port = card->curr_wr_port;
		if (++card->curr_wr_port == card->mp_end_port)
			card->curr_wr_port = reg->start_wr_port;
	} else {
		adapter->data_sent = true;
		return -EBUSY;
	}

	if ((card->has_control_mask) && (*port == CTRL_PORT)) {
		mwifiex_dbg(adapter, ERROR,
			    "invalid data port=%d cur port=%d mp_wr_bitmap=0x%08x -> 0x%08x\n",
			    *port, card->curr_wr_port, wr_bitmap,
			    card->mp_wr_bitmap);
		return -1;
	}

	mwifiex_dbg(adapter, DATA,
		    "data: port=%d mp_wr_bitmap=0x%08x -> 0x%08x\n",
		    *port, wr_bitmap, card->mp_wr_bitmap);

	return 0;
}