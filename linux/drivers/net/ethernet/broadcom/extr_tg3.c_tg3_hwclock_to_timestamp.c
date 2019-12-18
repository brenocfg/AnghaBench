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
typedef  int u64 ;
struct tg3 {scalar_t__ ptp_adjust; } ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;

/* Variables and functions */
 int TG3_TSTAMP_MASK ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_to_ktime (scalar_t__) ; 

__attribute__((used)) static void tg3_hwclock_to_timestamp(struct tg3 *tp, u64 hwclock,
				     struct skb_shared_hwtstamps *timestamp)
{
	memset(timestamp, 0, sizeof(struct skb_shared_hwtstamps));
	timestamp->hwtstamp  = ns_to_ktime((hwclock & TG3_TSTAMP_MASK) +
					   tp->ptp_adjust);
}