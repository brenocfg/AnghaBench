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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct pci_dev {int dummy; } ;
struct pch_gbe_adapter {struct pci_dev* ptp_pdev; int /*<<< orphan*/  hwts_rx_en; } ;

/* Variables and functions */
 int RX_SNAPSHOT_LOCKED ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int pch_ch_event_read (struct pci_dev*) ; 
 int /*<<< orphan*/  pch_ch_event_write (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pch_ptp_match (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_rx_snap_read (struct pci_dev*) ; 
 int pch_src_uuid_hi_read (struct pci_dev*) ; 
 int pch_src_uuid_lo_read (struct pci_dev*) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 

__attribute__((used)) static void
pch_rx_timestamp(struct pch_gbe_adapter *adapter, struct sk_buff *skb)
{
	struct skb_shared_hwtstamps *shhwtstamps;
	struct pci_dev *pdev;
	u64 ns;
	u32 hi, lo, val;
	u16 uid, seq;

	if (!adapter->hwts_rx_en)
		return;

	/* Get ieee1588's dev information */
	pdev = adapter->ptp_pdev;

	val = pch_ch_event_read(pdev);

	if (!(val & RX_SNAPSHOT_LOCKED))
		return;

	lo = pch_src_uuid_lo_read(pdev);
	hi = pch_src_uuid_hi_read(pdev);

	uid = hi & 0xffff;
	seq = (hi >> 16) & 0xffff;

	if (!pch_ptp_match(skb, htons(uid), htonl(lo), htons(seq)))
		goto out;

	ns = pch_rx_snap_read(pdev);

	shhwtstamps = skb_hwtstamps(skb);
	memset(shhwtstamps, 0, sizeof(*shhwtstamps));
	shhwtstamps->hwtstamp = ns_to_ktime(ns);
out:
	pch_ch_event_write(pdev, RX_SNAPSHOT_LOCKED);
}