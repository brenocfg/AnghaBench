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
struct lan743x_tx_descriptor {unsigned int data0; scalar_t__ data3; scalar_t__ data2; scalar_t__ data1; } ;
struct lan743x_tx_buffer_info {int /*<<< orphan*/  flags; scalar_t__ buffer_length; scalar_t__ dma_ptr; int /*<<< orphan*/ * skb; } ;
struct lan743x_tx {unsigned int frame_data0; size_t frame_tail; struct lan743x_tx_buffer_info* buffer_info; struct lan743x_tx_descriptor* ring_cpu_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_BUFFER_INFO_FLAG_ACTIVE ; 
 unsigned int TX_DESC_DATA0_DTYPE_EXT_ ; 
 unsigned int TX_DESC_DATA0_EXT_ ; 
 unsigned int TX_DESC_DATA0_EXT_LSO_ ; 
 unsigned int TX_DESC_DATA0_EXT_PAY_LENGTH_MASK_ ; 
 unsigned int TX_DESC_DATA0_IOC_ ; 
 unsigned int TX_DESC_DATA0_LS_ ; 
 size_t lan743x_tx_next_index (struct lan743x_tx*,size_t) ; 

__attribute__((used)) static void lan743x_tx_frame_add_lso(struct lan743x_tx *tx,
				     unsigned int frame_length,
				     int nr_frags)
{
	/* called only from within lan743x_tx_xmit_frame.
	 * assuming tx->ring_lock has already been acquired.
	 */
	struct lan743x_tx_descriptor *tx_descriptor = NULL;
	struct lan743x_tx_buffer_info *buffer_info = NULL;

	/* wrap up previous descriptor */
	tx->frame_data0 |= TX_DESC_DATA0_EXT_;
	if (nr_frags <= 0) {
		tx->frame_data0 |= TX_DESC_DATA0_LS_;
		tx->frame_data0 |= TX_DESC_DATA0_IOC_;
	}
	tx_descriptor = &tx->ring_cpu_ptr[tx->frame_tail];
	tx_descriptor->data0 = tx->frame_data0;

	/* move to next descriptor */
	tx->frame_tail = lan743x_tx_next_index(tx, tx->frame_tail);
	tx_descriptor = &tx->ring_cpu_ptr[tx->frame_tail];
	buffer_info = &tx->buffer_info[tx->frame_tail];

	/* add extension descriptor */
	tx_descriptor->data1 = 0;
	tx_descriptor->data2 = 0;
	tx_descriptor->data3 = 0;

	buffer_info->skb = NULL;
	buffer_info->dma_ptr = 0;
	buffer_info->buffer_length = 0;
	buffer_info->flags |= TX_BUFFER_INFO_FLAG_ACTIVE;

	tx->frame_data0 = (frame_length & TX_DESC_DATA0_EXT_PAY_LENGTH_MASK_) |
			  TX_DESC_DATA0_DTYPE_EXT_ |
			  TX_DESC_DATA0_EXT_LSO_;

	/* data0 will be programmed in one of other frame assembler functions */
}