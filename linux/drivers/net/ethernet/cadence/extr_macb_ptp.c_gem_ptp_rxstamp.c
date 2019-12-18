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
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct macb_dma_desc_ptp {int /*<<< orphan*/  ts_2; int /*<<< orphan*/  ts_1; } ;
struct macb_dma_desc {int /*<<< orphan*/  addr; } ;
struct macb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RXVALID ; 
 scalar_t__ GEM_BFEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gem_hw_timestamp (struct macb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec64*) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct macb_dma_desc_ptp* macb_ptp_desc (struct macb*,struct macb_dma_desc*) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 

void gem_ptp_rxstamp(struct macb *bp, struct sk_buff *skb,
		     struct macb_dma_desc *desc)
{
	struct skb_shared_hwtstamps *shhwtstamps = skb_hwtstamps(skb);
	struct macb_dma_desc_ptp *desc_ptp;
	struct timespec64 ts;

	if (GEM_BFEXT(DMA_RXVALID, desc->addr)) {
		desc_ptp = macb_ptp_desc(bp, desc);
		gem_hw_timestamp(bp, desc_ptp->ts_1, desc_ptp->ts_2, &ts);
		memset(shhwtstamps, 0, sizeof(struct skb_shared_hwtstamps));
		shhwtstamps->hwtstamp = ktime_set(ts.tv_sec, ts.tv_nsec);
	}
}