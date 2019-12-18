#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int msg_seq; } ;
struct TYPE_4__ {TYPE_1__ mcu; } ;
struct mt76_dev {TYPE_2__ mmio; } ;
struct mt7603_mcu_txd {int seq; int cid; int ext_cid; int ext_cid_ack; int /*<<< orphan*/  set_query; int /*<<< orphan*/  pkt_type; void* pq_id; void* len; } ;
struct mt7603_dev {struct mt76_dev mt76; scalar_t__ mcu_running; } ;

/* Variables and functions */
 int MCU_CMD_EXT_CID ; 
 int MCU_CMD_FW_SCATTER ; 
 int /*<<< orphan*/  MCU_PKT_ID ; 
 int /*<<< orphan*/  MCU_PORT_QUEUE ; 
 int /*<<< orphan*/  MCU_PORT_QUEUE_FW ; 
 int /*<<< orphan*/  MCU_Q_NA ; 
 int /*<<< orphan*/  MCU_Q_SET ; 
 int /*<<< orphan*/  MT_TXQ_MCU ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mt7603_mcu_txd*,int /*<<< orphan*/ ,int) ; 
 int mt76_tx_queue_skb_raw (struct mt7603_dev*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int
__mt7603_mcu_msg_send(struct mt7603_dev *dev, struct sk_buff *skb,
		      int cmd, int *wait_seq)
{
	int hdrlen = dev->mcu_running ? sizeof(struct mt7603_mcu_txd) : 12;
	struct mt76_dev *mdev = &dev->mt76;
	struct mt7603_mcu_txd *txd;
	u8 seq;

	seq = ++mdev->mmio.mcu.msg_seq & 0xf;
	if (!seq)
		seq = ++mdev->mmio.mcu.msg_seq & 0xf;

	txd = (struct mt7603_mcu_txd *)skb_push(skb, hdrlen);
	memset(txd, 0, hdrlen);

	txd->len = cpu_to_le16(skb->len);
	if (cmd == -MCU_CMD_FW_SCATTER)
		txd->pq_id = cpu_to_le16(MCU_PORT_QUEUE_FW);
	else
		txd->pq_id = cpu_to_le16(MCU_PORT_QUEUE);
	txd->pkt_type = MCU_PKT_ID;
	txd->seq = seq;

	if (cmd < 0) {
		txd->cid = -cmd;
		txd->set_query = MCU_Q_NA;
	} else {
		txd->cid = MCU_CMD_EXT_CID;
		txd->ext_cid = cmd;
		txd->set_query = MCU_Q_SET;
		txd->ext_cid_ack = 1;
	}

	if (wait_seq)
		*wait_seq = seq;

	return mt76_tx_queue_skb_raw(dev, MT_TXQ_MCU, skb, 0);
}