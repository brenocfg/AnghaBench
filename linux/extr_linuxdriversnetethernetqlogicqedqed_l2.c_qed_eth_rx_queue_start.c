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
typedef  int /*<<< orphan*/  u16 ;
struct qed_rxq_start_ret_params {void* p_handle; int /*<<< orphan*/  p_prod; } ;
struct qed_queue_start_common_params {int dummy; } ;
struct qed_queue_cid {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_PF (int /*<<< orphan*/ ) ; 
 int qed_eth_pf_rx_queue_start (struct qed_hwfn*,struct qed_queue_cid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_eth_queue_cid_release (struct qed_hwfn*,struct qed_queue_cid*) ; 
 struct qed_queue_cid* qed_eth_queue_to_cid_pf (struct qed_hwfn*,int /*<<< orphan*/ ,int,struct qed_queue_start_common_params*) ; 
 int qed_vf_pf_rxq_start (struct qed_hwfn*,struct qed_queue_cid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qed_eth_rx_queue_start(struct qed_hwfn *p_hwfn,
		       u16 opaque_fid,
		       struct qed_queue_start_common_params *p_params,
		       u16 bd_max_bytes,
		       dma_addr_t bd_chain_phys_addr,
		       dma_addr_t cqe_pbl_addr,
		       u16 cqe_pbl_size,
		       struct qed_rxq_start_ret_params *p_ret_params)
{
	struct qed_queue_cid *p_cid;
	int rc;

	/* Allocate a CID for the queue */
	p_cid = qed_eth_queue_to_cid_pf(p_hwfn, opaque_fid, true, p_params);
	if (!p_cid)
		return -ENOMEM;

	if (IS_PF(p_hwfn->cdev)) {
		rc = qed_eth_pf_rx_queue_start(p_hwfn, p_cid,
					       bd_max_bytes,
					       bd_chain_phys_addr,
					       cqe_pbl_addr, cqe_pbl_size,
					       &p_ret_params->p_prod);
	} else {
		rc = qed_vf_pf_rxq_start(p_hwfn, p_cid,
					 bd_max_bytes,
					 bd_chain_phys_addr,
					 cqe_pbl_addr,
					 cqe_pbl_size, &p_ret_params->p_prod);
	}

	/* Provide the caller with a reference to as handler */
	if (rc)
		qed_eth_queue_cid_release(p_hwfn, p_cid);
	else
		p_ret_params->p_handle = (void *)p_cid;

	return rc;
}