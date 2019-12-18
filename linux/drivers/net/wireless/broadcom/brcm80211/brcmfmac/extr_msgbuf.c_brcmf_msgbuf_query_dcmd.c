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
typedef  scalar_t__ uint ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct brcmf_pub {TYPE_1__* proto; } ;
struct brcmf_msgbuf {int ctl_completed; scalar_t__ ioctl_resp_ret_len; int ioctl_resp_status; int /*<<< orphan*/  ioctl_resp_pktid; int /*<<< orphan*/  rx_pktids; TYPE_3__* drvr; } ;
struct TYPE_6__ {TYPE_2__* bus_if; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ pd; } ;

/* Variables and functions */
 int EBADF ; 
 int EIO ; 
 int /*<<< orphan*/  MSGBUF ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__) ; 
 struct sk_buff* brcmf_msgbuf_get_pktid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int brcmf_msgbuf_ioctl_resp_wait (struct brcmf_msgbuf*) ; 
 int brcmf_msgbuf_tx_ioctl (struct brcmf_pub*,int,scalar_t__,void*,scalar_t__) ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int brcmf_msgbuf_query_dcmd(struct brcmf_pub *drvr, int ifidx,
				   uint cmd, void *buf, uint len, int *fwerr)
{
	struct brcmf_msgbuf *msgbuf = (struct brcmf_msgbuf *)drvr->proto->pd;
	struct sk_buff *skb = NULL;
	int timeout;
	int err;

	brcmf_dbg(MSGBUF, "ifidx=%d, cmd=%d, len=%d\n", ifidx, cmd, len);
	*fwerr = 0;
	msgbuf->ctl_completed = false;
	err = brcmf_msgbuf_tx_ioctl(drvr, ifidx, cmd, buf, len);
	if (err)
		return err;

	timeout = brcmf_msgbuf_ioctl_resp_wait(msgbuf);
	if (!timeout) {
		bphy_err(drvr, "Timeout on response for query command\n");
		return -EIO;
	}

	skb = brcmf_msgbuf_get_pktid(msgbuf->drvr->bus_if->dev,
				     msgbuf->rx_pktids,
				     msgbuf->ioctl_resp_pktid);
	if (msgbuf->ioctl_resp_ret_len != 0) {
		if (!skb)
			return -EBADF;

		memcpy(buf, skb->data, (len < msgbuf->ioctl_resp_ret_len) ?
				       len : msgbuf->ioctl_resp_ret_len);
	}
	brcmu_pkt_buf_free_skb(skb);

	*fwerr = msgbuf->ioctl_resp_status;
	return 0;
}