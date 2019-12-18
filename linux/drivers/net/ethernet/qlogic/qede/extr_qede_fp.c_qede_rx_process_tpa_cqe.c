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
union eth_rx_cqe {int /*<<< orphan*/  fast_path_tpa_end; int /*<<< orphan*/  fast_path_tpa_cont; int /*<<< orphan*/  fast_path_tpa_start; } ;
struct qede_rx_queue {int dummy; } ;
struct qede_fastpath {int dummy; } ;
struct qede_dev {int dummy; } ;
typedef  enum eth_rx_cqe_type { ____Placeholder_eth_rx_cqe_type } eth_rx_cqe_type ;

/* Variables and functions */
#define  ETH_RX_CQE_TYPE_TPA_CONT 130 
#define  ETH_RX_CQE_TYPE_TPA_END 129 
#define  ETH_RX_CQE_TYPE_TPA_START 128 
 int /*<<< orphan*/  qede_tpa_cont (struct qede_dev*,struct qede_rx_queue*,int /*<<< orphan*/ *) ; 
 int qede_tpa_end (struct qede_dev*,struct qede_fastpath*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qede_tpa_start (struct qede_dev*,struct qede_rx_queue*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qede_rx_process_tpa_cqe(struct qede_dev *edev,
				   struct qede_fastpath *fp,
				   struct qede_rx_queue *rxq,
				   union eth_rx_cqe *cqe,
				   enum eth_rx_cqe_type type)
{
	switch (type) {
	case ETH_RX_CQE_TYPE_TPA_START:
		qede_tpa_start(edev, rxq, &cqe->fast_path_tpa_start);
		return 0;
	case ETH_RX_CQE_TYPE_TPA_CONT:
		qede_tpa_cont(edev, rxq, &cqe->fast_path_tpa_cont);
		return 0;
	case ETH_RX_CQE_TYPE_TPA_END:
		return qede_tpa_end(edev, fp, &cqe->fast_path_tpa_end);
	default:
		return 0;
	}
}