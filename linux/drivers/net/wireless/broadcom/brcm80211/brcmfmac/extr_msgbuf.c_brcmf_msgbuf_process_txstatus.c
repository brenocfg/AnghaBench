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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ifidx; int /*<<< orphan*/  request_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  flow_ring_id; } ;
struct msgbuf_tx_status {TYPE_3__ msg; TYPE_1__ compl_hdr; } ;
struct brcmf_msgbuf {TYPE_4__* drvr; struct brcmf_commonring** flowrings; int /*<<< orphan*/  txstatus_done_map; int /*<<< orphan*/  tx_pktids; } ;
struct brcmf_commonring {int /*<<< orphan*/  outstanding_tx; } ;
struct TYPE_8__ {TYPE_2__* bus_if; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BRCMF_H2D_MSGRING_FLOWRING_IDSTART ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_get_ifp (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct sk_buff* brcmf_msgbuf_get_pktid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_txfinalize (int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brcmf_msgbuf_process_txstatus(struct brcmf_msgbuf *msgbuf, void *buf)
{
	struct brcmf_commonring *commonring;
	struct msgbuf_tx_status *tx_status;
	u32 idx;
	struct sk_buff *skb;
	u16 flowid;

	tx_status = (struct msgbuf_tx_status *)buf;
	idx = le32_to_cpu(tx_status->msg.request_id) - 1;
	flowid = le16_to_cpu(tx_status->compl_hdr.flow_ring_id);
	flowid -= BRCMF_H2D_MSGRING_FLOWRING_IDSTART;
	skb = brcmf_msgbuf_get_pktid(msgbuf->drvr->bus_if->dev,
				     msgbuf->tx_pktids, idx);
	if (!skb)
		return;

	set_bit(flowid, msgbuf->txstatus_done_map);
	commonring = msgbuf->flowrings[flowid];
	atomic_dec(&commonring->outstanding_tx);

	brcmf_txfinalize(brcmf_get_ifp(msgbuf->drvr, tx_status->msg.ifidx),
			 skb, true);
}