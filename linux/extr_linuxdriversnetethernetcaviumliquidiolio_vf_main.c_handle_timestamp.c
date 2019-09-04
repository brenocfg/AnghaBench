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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {scalar_t__ cb; } ;
struct octnet_buf_free_info {struct octeon_soft_command* sc; struct lio* lio; } ;
struct octeon_soft_command {scalar_t__ virtrptr; } ;
struct octeon_device {TYPE_1__* pci_dev; } ;
struct oct_timestamp_resp {scalar_t__ timestamp; } ;
struct lio {scalar_t__ ptp_adjust; int /*<<< orphan*/  netdev; struct octeon_device* oct_dev; } ;
struct TYPE_4__ {int tx_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVM_CAST64 (scalar_t__) ; 
 scalar_t__ OCTEON_REQUEST_DONE ; 
 int SKBTX_IN_PROGRESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct lio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct sk_buff*,unsigned long long) ; 
 int /*<<< orphan*/  ns_to_ktime (scalar_t__) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_swap_8B_data (scalar_t__*,int) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 
 int /*<<< orphan*/  tx_buffer_free (struct sk_buff*) ; 
 int /*<<< orphan*/  tx_done ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void handle_timestamp(struct octeon_device *oct, u32 status, void *buf)
{
	struct sk_buff *skb = (struct sk_buff *)buf;
	struct octnet_buf_free_info *finfo;
	struct oct_timestamp_resp *resp;
	struct octeon_soft_command *sc;
	struct lio *lio;

	finfo = (struct octnet_buf_free_info *)skb->cb;
	lio = finfo->lio;
	sc = finfo->sc;
	oct = lio->oct_dev;
	resp = (struct oct_timestamp_resp *)sc->virtrptr;

	if (status != OCTEON_REQUEST_DONE) {
		dev_err(&oct->pci_dev->dev, "Tx timestamp instruction failed. Status: %llx\n",
			CVM_CAST64(status));
		resp->timestamp = 0;
	}

	octeon_swap_8B_data(&resp->timestamp, 1);

	if (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS)) {
		struct skb_shared_hwtstamps ts;
		u64 ns = resp->timestamp;

		netif_info(lio, tx_done, lio->netdev,
			   "Got resulting SKBTX_HW_TSTAMP skb=%p ns=%016llu\n",
			   skb, (unsigned long long)ns);
		ts.hwtstamp = ns_to_ktime(ns + lio->ptp_adjust);
		skb_tstamp_tx(skb, &ts);
	}

	octeon_free_soft_command(oct, sc);
	tx_buffer_free(skb);
}