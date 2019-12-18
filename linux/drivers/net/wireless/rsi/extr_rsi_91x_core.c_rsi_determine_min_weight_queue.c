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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct wmm_qinfo {int /*<<< orphan*/  weight; scalar_t__ pkt_contended; } ;
struct rsi_common {int /*<<< orphan*/  min_weight; int /*<<< orphan*/ * tx_queue; struct wmm_qinfo* tx_qinfo; } ;

/* Variables and functions */
 size_t NUM_EDCA_QUEUES ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 rsi_determine_min_weight_queue(struct rsi_common *common)
{
	struct wmm_qinfo *tx_qinfo = common->tx_qinfo;
	u32 q_len = 0;
	u8 ii = 0;

	for (ii = 0; ii < NUM_EDCA_QUEUES; ii++) {
		q_len = skb_queue_len(&common->tx_queue[ii]);
		if ((tx_qinfo[ii].pkt_contended) && q_len) {
			common->min_weight = tx_qinfo[ii].weight;
			break;
		}
	}
	return ii;
}