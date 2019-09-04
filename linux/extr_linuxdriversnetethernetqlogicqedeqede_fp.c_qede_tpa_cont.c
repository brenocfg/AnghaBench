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
struct qede_rx_queue {int dummy; } ;
struct qede_dev {int dummy; } ;
struct eth_fast_path_rx_tpa_cont_cqe {scalar_t__* len_list; int /*<<< orphan*/  tpa_agg_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  qede_fill_frag_skb (struct qede_dev*,struct qede_rx_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void qede_tpa_cont(struct qede_dev *edev,
				 struct qede_rx_queue *rxq,
				 struct eth_fast_path_rx_tpa_cont_cqe *cqe)
{
	int i;

	for (i = 0; cqe->len_list[i]; i++)
		qede_fill_frag_skb(edev, rxq, cqe->tpa_agg_index,
				   le16_to_cpu(cqe->len_list[i]));

	if (unlikely(i > 1))
		DP_ERR(edev,
		       "Strange - TPA cont with more than a single len_list entry\n");
}