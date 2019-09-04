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
struct macb {int dummy; } ;
typedef  int /*<<< orphan*/  shhwtstamps ;

/* Variables and functions */
 int /*<<< orphan*/  gem_hw_timestamp (struct macb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec64*) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 

__attribute__((used)) static void gem_tstamp_tx(struct macb *bp, struct sk_buff *skb,
			  struct macb_dma_desc_ptp *desc_ptp)
{
	struct skb_shared_hwtstamps shhwtstamps;
	struct timespec64 ts;

	gem_hw_timestamp(bp, desc_ptp->ts_1, desc_ptp->ts_2, &ts);
	memset(&shhwtstamps, 0, sizeof(shhwtstamps));
	shhwtstamps.hwtstamp = ktime_set(ts.tv_sec, ts.tv_nsec);
	skb_tstamp_tx(skb, &shhwtstamps);
}