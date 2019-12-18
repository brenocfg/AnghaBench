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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {TYPE_2__* ndev; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int ENODATA ; 
 int brcmf_proto_hdrpull (struct brcmf_pub*,int,struct sk_buff*,struct brcmf_if**) ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 

__attribute__((used)) static int brcmf_rx_hdrpull(struct brcmf_pub *drvr, struct sk_buff *skb,
			    struct brcmf_if **ifp)
{
	int ret;

	/* process and remove protocol-specific header */
	ret = brcmf_proto_hdrpull(drvr, true, skb, ifp);

	if (ret || !(*ifp) || !(*ifp)->ndev) {
		if (ret != -ENODATA && *ifp)
			(*ifp)->ndev->stats.rx_errors++;
		brcmu_pkt_buf_free_skb(skb);
		return -ENODATA;
	}

	skb->protocol = eth_type_trans(skb, (*ifp)->ndev);
	return 0;
}