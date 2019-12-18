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
struct qed_hwfn {int dummy; } ;
struct eth_slow_path_rx_cqe {int /*<<< orphan*/  ramrod_cmd_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int qed_cqe_completion (struct qed_hwfn*,struct eth_slow_path_rx_cqe*,int /*<<< orphan*/ ) ; 

int qed_eth_cqe_completion(struct qed_hwfn *p_hwfn,
			   struct eth_slow_path_rx_cqe *cqe)
{
	int rc;

	rc = qed_cqe_completion(p_hwfn, cqe, PROTOCOLID_ETH);
	if (rc)
		DP_NOTICE(p_hwfn,
			  "Failed to handle RXQ CQE [cmd 0x%02x]\n",
			  cqe->ramrod_cmd_id);

	return rc;
}