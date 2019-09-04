#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct igb_q_vector {struct igb_adapter* adapter; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_5__ {TYPE_2__ mac; } ;
struct igb_adapter {int link_speed; TYPE_1__ hw; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_7__ {int /*<<< orphan*/  hwtstamp; } ;

/* Variables and functions */
 int IGB_I210_RX_LATENCY_10 ; 
 int IGB_I210_RX_LATENCY_100 ; 
 int IGB_I210_RX_LATENCY_1000 ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 scalar_t__ e1000_i210 ; 
 int /*<<< orphan*/  igb_ptp_systim_to_hwtstamp (struct igb_adapter*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_sub_ns (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_3__* skb_hwtstamps (struct sk_buff*) ; 

void igb_ptp_rx_pktstamp(struct igb_q_vector *q_vector, void *va,
			 struct sk_buff *skb)
{
	__le64 *regval = (__le64 *)va;
	struct igb_adapter *adapter = q_vector->adapter;
	int adjust = 0;

	/* The timestamp is recorded in little endian format.
	 * DWORD: 0        1        2        3
	 * Field: Reserved Reserved SYSTIML  SYSTIMH
	 */
	igb_ptp_systim_to_hwtstamp(adapter, skb_hwtstamps(skb),
				   le64_to_cpu(regval[1]));

	/* adjust timestamp for the RX latency based on link speed */
	if (adapter->hw.mac.type == e1000_i210) {
		switch (adapter->link_speed) {
		case SPEED_10:
			adjust = IGB_I210_RX_LATENCY_10;
			break;
		case SPEED_100:
			adjust = IGB_I210_RX_LATENCY_100;
			break;
		case SPEED_1000:
			adjust = IGB_I210_RX_LATENCY_1000;
			break;
		}
	}
	skb_hwtstamps(skb)->hwtstamp =
		ktime_sub_ns(skb_hwtstamps(skb)->hwtstamp, adjust);
}