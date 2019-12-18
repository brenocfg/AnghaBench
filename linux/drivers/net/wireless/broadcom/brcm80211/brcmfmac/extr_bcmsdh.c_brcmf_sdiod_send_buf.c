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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct brcmf_sdio_dev {int /*<<< orphan*/  func2; TYPE_1__* cc_core; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SBSDIO_SB_ACCESS_2_4B_FLAG ; 
 int /*<<< orphan*/  SBSDIO_SB_OFT_ADDR_MASK ; 
 int /*<<< orphan*/  brcmf_err (char*,int /*<<< orphan*/ ) ; 
 int brcmf_sdiod_set_backplane_window (struct brcmf_sdio_dev*,int /*<<< orphan*/ ) ; 
 int brcmf_sdiod_skbuff_write (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (struct sk_buff*) ; 
 struct sk_buff* brcmu_pkt_buf_get_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int brcmf_sdiod_send_buf(struct brcmf_sdio_dev *sdiodev, u8 *buf, uint nbytes)
{
	struct sk_buff *mypkt;
	u32 addr = sdiodev->cc_core->base;
	int err;

	mypkt = brcmu_pkt_buf_get_skb(nbytes);

	if (!mypkt) {
		brcmf_err("brcmu_pkt_buf_get_skb failed: len %d\n",
			  nbytes);
		return -EIO;
	}

	memcpy(mypkt->data, buf, nbytes);

	err = brcmf_sdiod_set_backplane_window(sdiodev, addr);
	if (err)
		goto out;

	addr &= SBSDIO_SB_OFT_ADDR_MASK;
	addr |= SBSDIO_SB_ACCESS_2_4B_FLAG;

	err = brcmf_sdiod_skbuff_write(sdiodev, sdiodev->func2, addr, mypkt);
out:
	brcmu_pkt_buf_free_skb(mypkt);

	return err;
}