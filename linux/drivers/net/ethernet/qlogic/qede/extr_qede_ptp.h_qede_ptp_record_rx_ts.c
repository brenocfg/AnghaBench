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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ pars_flags; } ;
union eth_rx_cqe {TYPE_2__ fast_path_regular; } ;
struct sk_buff {int dummy; } ;
struct qede_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int PARSING_AND_ERR_FLAGS_TIMESTAMPRECORDED_SHIFT ; 
 int PARSING_AND_ERR_FLAGS_TIMESYNCPKT_SHIFT ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  qede_ptp_rx_ts (struct qede_dev*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void qede_ptp_record_rx_ts(struct qede_dev *edev,
					 union eth_rx_cqe *cqe,
					 struct sk_buff *skb)
{
	/* Check if this packet was timestamped */
	if (unlikely(le16_to_cpu(cqe->fast_path_regular.pars_flags.flags) &
		     (1 << PARSING_AND_ERR_FLAGS_TIMESTAMPRECORDED_SHIFT))) {
		if (likely(le16_to_cpu(cqe->fast_path_regular.pars_flags.flags)
		    & (1 << PARSING_AND_ERR_FLAGS_TIMESYNCPKT_SHIFT))) {
			qede_ptp_rx_ts(edev, skb);
		} else {
			DP_INFO(edev,
				"Timestamp recorded for non PTP packets\n");
		}
	}
}