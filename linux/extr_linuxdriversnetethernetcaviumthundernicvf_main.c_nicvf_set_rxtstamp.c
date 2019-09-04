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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {scalar_t__ data; } ;
struct nicvf {int /*<<< orphan*/  ptp_clock; int /*<<< orphan*/  hw_rx_tstamp; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_2__ {int /*<<< orphan*/  hwtstamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cavium_ptp_tstamp2time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_hwtstamps (struct sk_buff*) ; 

__attribute__((used)) static inline void nicvf_set_rxtstamp(struct nicvf *nic, struct sk_buff *skb)
{
	u64 ns;

	if (!nic->ptp_clock || !nic->hw_rx_tstamp)
		return;

	/* The first 8 bytes is the timestamp */
	ns = cavium_ptp_tstamp2time(nic->ptp_clock,
				    be64_to_cpu(*(__be64 *)skb->data));
	skb_hwtstamps(skb)->hwtstamp = ns_to_ktime(ns);

	__skb_pull(skb, 8);
}