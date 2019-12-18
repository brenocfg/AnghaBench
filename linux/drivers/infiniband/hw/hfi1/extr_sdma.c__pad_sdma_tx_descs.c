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
struct sdma_txreq {scalar_t__ num_desc; scalar_t__ desc_limit; int packet_len; } ;
struct hfi1_devdata {int /*<<< orphan*/  sdma_pad_phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_MAP_NONE ; 
 int /*<<< orphan*/  __sdma_txclean (struct hfi1_devdata*,struct sdma_txreq*) ; 
 int _extend_sdma_tx_descs (struct hfi1_devdata*,struct sdma_txreq*) ; 
 int /*<<< orphan*/  _sdma_close_tx (struct hfi1_devdata*,struct sdma_txreq*) ; 
 int /*<<< orphan*/  make_tx_sdma_desc (struct sdma_txreq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

int _pad_sdma_tx_descs(struct hfi1_devdata *dd, struct sdma_txreq *tx)
{
	int rval = 0;

	tx->num_desc++;
	if ((unlikely(tx->num_desc == tx->desc_limit))) {
		rval = _extend_sdma_tx_descs(dd, tx);
		if (rval) {
			__sdma_txclean(dd, tx);
			return rval;
		}
	}
	/* finish the one just added */
	make_tx_sdma_desc(
		tx,
		SDMA_MAP_NONE,
		dd->sdma_pad_phys,
		sizeof(u32) - (tx->packet_len & (sizeof(u32) - 1)));
	_sdma_close_tx(dd, tx);
	return rval;
}