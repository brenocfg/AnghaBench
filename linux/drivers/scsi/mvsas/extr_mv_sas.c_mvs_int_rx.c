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
typedef  int u32 ;
struct mvs_info {int rx_cons; int /*<<< orphan*/ * rx; } ;
struct TYPE_2__ {int (* rx_update ) (struct mvs_info*) ;int /*<<< orphan*/  (* int_full ) (struct mvs_info*) ;} ;

/* Variables and functions */
 TYPE_1__* MVS_CHIP_DISP ; 
 int MVS_RX_RING_SZ ; 
 int RXQ_ATTN ; 
 int RXQ_DONE ; 
 int RXQ_ERR ; 
 int RXQ_SLOT_RESET ; 
 int RX_RING_SZ_MASK ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mvs_slot_complete (struct mvs_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_slot_free (struct mvs_info*,int) ; 
 int stub1 (struct mvs_info*) ; 
 int /*<<< orphan*/  stub2 (struct mvs_info*) ; 
 scalar_t__ unlikely (int) ; 

int mvs_int_rx(struct mvs_info *mvi, bool self_clear)
{
	u32 rx_prod_idx, rx_desc;
	bool attn = false;

	/* the first dword in the RX ring is special: it contains
	 * a mirror of the hardware's RX producer index, so that
	 * we don't have to stall the CPU reading that register.
	 * The actual RX ring is offset by one dword, due to this.
	 */
	rx_prod_idx = mvi->rx_cons;
	mvi->rx_cons = le32_to_cpu(mvi->rx[0]);
	if (mvi->rx_cons == 0xfff)	/* h/w hasn't touched RX ring yet */
		return 0;

	/* The CMPL_Q may come late, read from register and try again
	* note: if coalescing is enabled,
	* it will need to read from register every time for sure
	*/
	if (unlikely(mvi->rx_cons == rx_prod_idx))
		mvi->rx_cons = MVS_CHIP_DISP->rx_update(mvi) & RX_RING_SZ_MASK;

	if (mvi->rx_cons == rx_prod_idx)
		return 0;

	while (mvi->rx_cons != rx_prod_idx) {
		/* increment our internal RX consumer pointer */
		rx_prod_idx = (rx_prod_idx + 1) & (MVS_RX_RING_SZ - 1);
		rx_desc = le32_to_cpu(mvi->rx[rx_prod_idx + 1]);

		if (likely(rx_desc & RXQ_DONE))
			mvs_slot_complete(mvi, rx_desc, 0);
		if (rx_desc & RXQ_ATTN) {
			attn = true;
		} else if (rx_desc & RXQ_ERR) {
			if (!(rx_desc & RXQ_DONE))
				mvs_slot_complete(mvi, rx_desc, 0);
		} else if (rx_desc & RXQ_SLOT_RESET) {
			mvs_slot_free(mvi, rx_desc);
		}
	}

	if (attn && self_clear)
		MVS_CHIP_DISP->int_full(mvi);
	return 0;
}