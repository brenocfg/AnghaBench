#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct sk_buff {int len; } ;
struct mt7615_mcu_txd {int seq; int cid; int ext_cid; int ext_cid_ack; int /*<<< orphan*/  s2d_index; int /*<<< orphan*/  set_query; int /*<<< orphan*/  pkt_type; void* pq_id; void* len; int /*<<< orphan*/ * txd; } ;
struct TYPE_4__ {int msg_seq; } ;
struct TYPE_5__ {TYPE_1__ mcu; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; TYPE_2__ mmio; } ;
struct mt7615_dev {TYPE_3__ mt76; } ;
typedef  enum mt76_txq_id { ____Placeholder_mt76_txq_id } mt76_txq_id ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int MCU_CMD_EXT_CID ; 
 int MCU_CMD_FW_SCATTER ; 
 int /*<<< orphan*/  MCU_PKT_ID ; 
 int MCU_PQ_ID (int,int) ; 
 int /*<<< orphan*/  MCU_Q_NA ; 
 int /*<<< orphan*/  MCU_Q_SET ; 
 int /*<<< orphan*/  MCU_S2D_H2N ; 
 int /*<<< orphan*/  MT76_STATE_MCU_RUNNING ; 
 int MT_HDR_FORMAT_CMD ; 
 int /*<<< orphan*/  MT_TXD0_P_IDX ; 
 int /*<<< orphan*/  MT_TXD0_Q_IDX ; 
 int /*<<< orphan*/  MT_TXD0_TX_BYTES ; 
 int /*<<< orphan*/  MT_TXD1_HDR_FORMAT ; 
 int MT_TXD1_LONG_FORMAT ; 
 int /*<<< orphan*/  MT_TXD1_PKT_FMT ; 
 int MT_TXQ_FWDL ; 
 int MT_TXQ_MCU ; 
 int MT_TX_MCU_PORT_RX_FWDL ; 
 int MT_TX_MCU_PORT_RX_Q0 ; 
 int MT_TX_PORT_IDX_MCU ; 
 int MT_TX_TYPE_CMD ; 
 int MT_TX_TYPE_FW ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (struct mt7615_mcu_txd*,int /*<<< orphan*/ ,int) ; 
 int mt76_tx_queue_skb_raw (struct mt7615_dev*,int,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __mt7615_mcu_msg_send(struct mt7615_dev *dev, struct sk_buff *skb,
				 int cmd, int *wait_seq)
{
	struct mt7615_mcu_txd *mcu_txd;
	u8 seq, q_idx, pkt_fmt;
	enum mt76_txq_id qid;
	u32 val;
	__le32 *txd;

	seq = ++dev->mt76.mmio.mcu.msg_seq & 0xf;
	if (!seq)
		seq = ++dev->mt76.mmio.mcu.msg_seq & 0xf;

	mcu_txd = (struct mt7615_mcu_txd *)skb_push(skb,
		   sizeof(struct mt7615_mcu_txd));
	memset(mcu_txd, 0, sizeof(struct mt7615_mcu_txd));

	if (cmd != -MCU_CMD_FW_SCATTER) {
		q_idx = MT_TX_MCU_PORT_RX_Q0;
		pkt_fmt = MT_TX_TYPE_CMD;
	} else {
		q_idx = MT_TX_MCU_PORT_RX_FWDL;
		pkt_fmt = MT_TX_TYPE_FW;
	}

	txd = mcu_txd->txd;

	val = FIELD_PREP(MT_TXD0_TX_BYTES, skb->len) |
	      FIELD_PREP(MT_TXD0_P_IDX, MT_TX_PORT_IDX_MCU) |
	      FIELD_PREP(MT_TXD0_Q_IDX, q_idx);
	txd[0] = cpu_to_le32(val);

	val = MT_TXD1_LONG_FORMAT |
	      FIELD_PREP(MT_TXD1_HDR_FORMAT, MT_HDR_FORMAT_CMD) |
	      FIELD_PREP(MT_TXD1_PKT_FMT, pkt_fmt);
	txd[1] = cpu_to_le32(val);

	mcu_txd->len = cpu_to_le16(skb->len - sizeof(mcu_txd->txd));
	mcu_txd->pq_id = cpu_to_le16(MCU_PQ_ID(MT_TX_PORT_IDX_MCU, q_idx));
	mcu_txd->pkt_type = MCU_PKT_ID;
	mcu_txd->seq = seq;

	if (cmd < 0) {
		mcu_txd->set_query = MCU_Q_NA;
		mcu_txd->cid = -cmd;
	} else {
		mcu_txd->cid = MCU_CMD_EXT_CID;
		mcu_txd->set_query = MCU_Q_SET;
		mcu_txd->ext_cid = cmd;
		mcu_txd->ext_cid_ack = 1;
	}
	mcu_txd->s2d_index = MCU_S2D_H2N;

	if (wait_seq)
		*wait_seq = seq;

	if (test_bit(MT76_STATE_MCU_RUNNING, &dev->mt76.state))
		qid = MT_TXQ_MCU;
	else
		qid = MT_TXQ_FWDL;

	return mt76_tx_queue_skb_raw(dev, qid, skb, 0);
}