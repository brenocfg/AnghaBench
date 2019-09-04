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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct fmdev {int /*<<< orphan*/  tx_task; int /*<<< orphan*/  tx_q; int /*<<< orphan*/  flag; } ;
struct fm_cmd_msg_hdr {int len; int dlen; int /*<<< orphan*/  rd_wr; scalar_t__ op; int /*<<< orphan*/  hdr; } ;
struct completion {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {struct completion* completion; scalar_t__ fm_op; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FM_CMD_MSG_HDR_SIZE ; 
 int /*<<< orphan*/  FM_FW_DW_INPROGRESS ; 
 scalar_t__ FM_INTERRUPT ; 
 int /*<<< orphan*/  FM_INTTASK_RUNNING ; 
 int /*<<< orphan*/  FM_PKT_LOGICAL_CHAN_NUMBER ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 TYPE_1__* fm_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  fmerr (char*,...) ; 
 struct fm_cmd_msg_hdr* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fm_send_cmd(struct fmdev *fmdev, u8 fm_op, u16 type,	void *payload,
		int payload_len, struct completion *wait_completion)
{
	struct sk_buff *skb;
	struct fm_cmd_msg_hdr *hdr;
	int size;

	if (fm_op >= FM_INTERRUPT) {
		fmerr("Invalid fm opcode - %d\n", fm_op);
		return -EINVAL;
	}
	if (test_bit(FM_FW_DW_INPROGRESS, &fmdev->flag) && payload == NULL) {
		fmerr("Payload data is NULL during fw download\n");
		return -EINVAL;
	}
	if (!test_bit(FM_FW_DW_INPROGRESS, &fmdev->flag))
		size =
		    FM_CMD_MSG_HDR_SIZE + ((payload == NULL) ? 0 : payload_len);
	else
		size = payload_len;

	skb = alloc_skb(size, GFP_ATOMIC);
	if (!skb) {
		fmerr("No memory to create new SKB\n");
		return -ENOMEM;
	}
	/*
	 * Don't fill FM header info for the commands which come from
	 * FM firmware file.
	 */
	if (!test_bit(FM_FW_DW_INPROGRESS, &fmdev->flag) ||
			test_bit(FM_INTTASK_RUNNING, &fmdev->flag)) {
		/* Fill command header info */
		hdr = skb_put(skb, FM_CMD_MSG_HDR_SIZE);
		hdr->hdr = FM_PKT_LOGICAL_CHAN_NUMBER;	/* 0x08 */

		/* 3 (fm_opcode,rd_wr,dlen) + payload len) */
		hdr->len = ((payload == NULL) ? 0 : payload_len) + 3;

		/* FM opcode */
		hdr->op = fm_op;

		/* read/write type */
		hdr->rd_wr = type;
		hdr->dlen = payload_len;
		fm_cb(skb)->fm_op = fm_op;

		/*
		 * If firmware download has finished and the command is
		 * not a read command then payload is != NULL - a write
		 * command with u16 payload - convert to be16
		 */
		if (payload != NULL)
			*(__be16 *)payload = cpu_to_be16(*(u16 *)payload);

	} else if (payload != NULL) {
		fm_cb(skb)->fm_op = *((u8 *)payload + 2);
	}
	if (payload != NULL)
		skb_put_data(skb, payload, payload_len);

	fm_cb(skb)->completion = wait_completion;
	skb_queue_tail(&fmdev->tx_q, skb);
	tasklet_schedule(&fmdev->tx_task);

	return 0;
}