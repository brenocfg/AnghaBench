#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int signal; int service; int length_low; int length_high; int ifs; } ;
struct TYPE_7__ {TYPE_2__ plcp; } ;
struct txentry_desc {int iv_offset; int length; scalar_t__ rate_mode; int key_idx; int cipher; int /*<<< orphan*/  flags; TYPE_3__ u; } ;
struct skb_frame_desc {int skb_dma; int /*<<< orphan*/  desc_len; int /*<<< orphan*/ * desc; int /*<<< orphan*/ * iv; } ;
struct queue_entry_priv_mmio {int /*<<< orphan*/ * desc; } ;
struct queue_entry {int entry_idx; TYPE_4__* queue; struct queue_entry_priv_mmio* priv_data; int /*<<< orphan*/  skb; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_8__ {int qid; int aifs; int cw_min; int cw_max; TYPE_1__* rt2x00dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_TXD_ACK ; 
 int /*<<< orphan*/  ENTRY_TXD_BURST ; 
 int /*<<< orphan*/  ENTRY_TXD_ENCRYPT ; 
 int /*<<< orphan*/  ENTRY_TXD_ENCRYPT_MMIC ; 
 int /*<<< orphan*/  ENTRY_TXD_ENCRYPT_PAIRWISE ; 
 int /*<<< orphan*/  ENTRY_TXD_GENERATE_SEQ ; 
 int /*<<< orphan*/  ENTRY_TXD_MORE_FRAG ; 
 int /*<<< orphan*/  ENTRY_TXD_REQ_TIMESTAMP ; 
 int /*<<< orphan*/  ENTRY_TXD_RETRY_MODE ; 
 int QID_BEACON ; 
 scalar_t__ RATE_MODE_OFDM ; 
 int /*<<< orphan*/  TXD_DESC_SIZE ; 
 int /*<<< orphan*/  TXD_W0_ACK ; 
 int /*<<< orphan*/  TXD_W0_BURST ; 
 int /*<<< orphan*/  TXD_W0_CIPHER_ALG ; 
 int /*<<< orphan*/  TXD_W0_DATABYTE_COUNT ; 
 int /*<<< orphan*/  TXD_W0_IFS ; 
 int /*<<< orphan*/  TXD_W0_KEY_INDEX ; 
 int /*<<< orphan*/  TXD_W0_KEY_TABLE ; 
 int /*<<< orphan*/  TXD_W0_MORE_FRAG ; 
 int /*<<< orphan*/  TXD_W0_OFDM ; 
 int /*<<< orphan*/  TXD_W0_OWNER_NIC ; 
 int /*<<< orphan*/  TXD_W0_RETRY_MODE ; 
 int /*<<< orphan*/  TXD_W0_TIMESTAMP ; 
 int /*<<< orphan*/  TXD_W0_TKIP_MIC ; 
 int /*<<< orphan*/  TXD_W0_VALID ; 
 int /*<<< orphan*/  TXD_W11_BUFFER_LENGTH0 ; 
 int /*<<< orphan*/  TXD_W1_AIFSN ; 
 int /*<<< orphan*/  TXD_W1_BUFFER_COUNT ; 
 int /*<<< orphan*/  TXD_W1_CWMAX ; 
 int /*<<< orphan*/  TXD_W1_CWMIN ; 
 int /*<<< orphan*/  TXD_W1_HOST_Q_ID ; 
 int /*<<< orphan*/  TXD_W1_HW_SEQUENCE ; 
 int /*<<< orphan*/  TXD_W1_IV_OFFSET ; 
 int /*<<< orphan*/  TXD_W2_PLCP_LENGTH_HIGH ; 
 int /*<<< orphan*/  TXD_W2_PLCP_LENGTH_LOW ; 
 int /*<<< orphan*/  TXD_W2_PLCP_SERVICE ; 
 int /*<<< orphan*/  TXD_W2_PLCP_SIGNAL ; 
 int /*<<< orphan*/  TXD_W5_PID_SUBTYPE ; 
 int /*<<< orphan*/  TXD_W5_PID_TYPE ; 
 int /*<<< orphan*/  TXD_W5_TX_POWER ; 
 int /*<<< orphan*/  TXD_W5_WAITING_DMA_DONE_INT ; 
 int /*<<< orphan*/  TXD_W6_BUFFER_PHYSICAL_ADDRESS ; 
 int /*<<< orphan*/  TXINFO_SIZE ; 
 int TXPOWER_TO_DEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rt2x00_desc_write (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct skb_frame_desc* get_skb_frame_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rt2x00_desc_write (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt61pci_write_tx_desc(struct queue_entry *entry,
				  struct txentry_desc *txdesc)
{
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	struct queue_entry_priv_mmio *entry_priv = entry->priv_data;
	__le32 *txd = entry_priv->desc;
	u32 word;

	/*
	 * Start writing the descriptor words.
	 */
	word = rt2x00_desc_read(txd, 1);
	rt2x00_set_field32(&word, TXD_W1_HOST_Q_ID, entry->queue->qid);
	rt2x00_set_field32(&word, TXD_W1_AIFSN, entry->queue->aifs);
	rt2x00_set_field32(&word, TXD_W1_CWMIN, entry->queue->cw_min);
	rt2x00_set_field32(&word, TXD_W1_CWMAX, entry->queue->cw_max);
	rt2x00_set_field32(&word, TXD_W1_IV_OFFSET, txdesc->iv_offset);
	rt2x00_set_field32(&word, TXD_W1_HW_SEQUENCE,
			   test_bit(ENTRY_TXD_GENERATE_SEQ, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W1_BUFFER_COUNT, 1);
	rt2x00_desc_write(txd, 1, word);

	word = rt2x00_desc_read(txd, 2);
	rt2x00_set_field32(&word, TXD_W2_PLCP_SIGNAL, txdesc->u.plcp.signal);
	rt2x00_set_field32(&word, TXD_W2_PLCP_SERVICE, txdesc->u.plcp.service);
	rt2x00_set_field32(&word, TXD_W2_PLCP_LENGTH_LOW,
			   txdesc->u.plcp.length_low);
	rt2x00_set_field32(&word, TXD_W2_PLCP_LENGTH_HIGH,
			   txdesc->u.plcp.length_high);
	rt2x00_desc_write(txd, 2, word);

	if (test_bit(ENTRY_TXD_ENCRYPT, &txdesc->flags)) {
		_rt2x00_desc_write(txd, 3, skbdesc->iv[0]);
		_rt2x00_desc_write(txd, 4, skbdesc->iv[1]);
	}

	word = rt2x00_desc_read(txd, 5);
	rt2x00_set_field32(&word, TXD_W5_PID_TYPE, entry->queue->qid);
	rt2x00_set_field32(&word, TXD_W5_PID_SUBTYPE, entry->entry_idx);
	rt2x00_set_field32(&word, TXD_W5_TX_POWER,
			   TXPOWER_TO_DEV(entry->queue->rt2x00dev->tx_power));
	rt2x00_set_field32(&word, TXD_W5_WAITING_DMA_DONE_INT, 1);
	rt2x00_desc_write(txd, 5, word);

	if (entry->queue->qid != QID_BEACON) {
		word = rt2x00_desc_read(txd, 6);
		rt2x00_set_field32(&word, TXD_W6_BUFFER_PHYSICAL_ADDRESS,
				   skbdesc->skb_dma);
		rt2x00_desc_write(txd, 6, word);

		word = rt2x00_desc_read(txd, 11);
		rt2x00_set_field32(&word, TXD_W11_BUFFER_LENGTH0,
				   txdesc->length);
		rt2x00_desc_write(txd, 11, word);
	}

	/*
	 * Writing TXD word 0 must the last to prevent a race condition with
	 * the device, whereby the device may take hold of the TXD before we
	 * finished updating it.
	 */
	word = rt2x00_desc_read(txd, 0);
	rt2x00_set_field32(&word, TXD_W0_OWNER_NIC, 1);
	rt2x00_set_field32(&word, TXD_W0_VALID, 1);
	rt2x00_set_field32(&word, TXD_W0_MORE_FRAG,
			   test_bit(ENTRY_TXD_MORE_FRAG, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_ACK,
			   test_bit(ENTRY_TXD_ACK, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_TIMESTAMP,
			   test_bit(ENTRY_TXD_REQ_TIMESTAMP, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_OFDM,
			   (txdesc->rate_mode == RATE_MODE_OFDM));
	rt2x00_set_field32(&word, TXD_W0_IFS, txdesc->u.plcp.ifs);
	rt2x00_set_field32(&word, TXD_W0_RETRY_MODE,
			   test_bit(ENTRY_TXD_RETRY_MODE, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_TKIP_MIC,
			   test_bit(ENTRY_TXD_ENCRYPT_MMIC, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_KEY_TABLE,
			   test_bit(ENTRY_TXD_ENCRYPT_PAIRWISE, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_KEY_INDEX, txdesc->key_idx);
	rt2x00_set_field32(&word, TXD_W0_DATABYTE_COUNT, txdesc->length);
	rt2x00_set_field32(&word, TXD_W0_BURST,
			   test_bit(ENTRY_TXD_BURST, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_CIPHER_ALG, txdesc->cipher);
	rt2x00_desc_write(txd, 0, word);

	/*
	 * Register descriptor details in skb frame descriptor.
	 */
	skbdesc->desc = txd;
	skbdesc->desc_len = (entry->queue->qid == QID_BEACON) ? TXINFO_SIZE :
			    TXD_DESC_SIZE;
}