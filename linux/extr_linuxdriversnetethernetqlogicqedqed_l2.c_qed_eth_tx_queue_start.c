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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qed_txq_start_ret_params {void* p_handle; int /*<<< orphan*/  p_doorbell; } ;
struct qed_queue_start_common_params {int dummy; } ;
struct qed_queue_cid {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_PF (int /*<<< orphan*/ ) ; 
 int qed_eth_pf_tx_queue_start (struct qed_hwfn*,struct qed_queue_cid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_eth_queue_cid_release (struct qed_hwfn*,struct qed_queue_cid*) ; 
 struct qed_queue_cid* qed_eth_queue_to_cid_pf (struct qed_hwfn*,int /*<<< orphan*/ ,int,struct qed_queue_start_common_params*) ; 
 int qed_vf_pf_txq_start (struct qed_hwfn*,struct qed_queue_cid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qed_eth_tx_queue_start(struct qed_hwfn *p_hwfn,
		       u16 opaque_fid,
		       struct qed_queue_start_common_params *p_params,
		       u8 tc,
		       dma_addr_t pbl_addr,
		       u16 pbl_size,
		       struct qed_txq_start_ret_params *p_ret_params)
{
	struct qed_queue_cid *p_cid;
	int rc;

	p_cid = qed_eth_queue_to_cid_pf(p_hwfn, opaque_fid, false, p_params);
	if (!p_cid)
		return -EINVAL;

	if (IS_PF(p_hwfn->cdev))
		rc = qed_eth_pf_tx_queue_start(p_hwfn, p_cid, tc,
					       pbl_addr, pbl_size,
					       &p_ret_params->p_doorbell);
	else
		rc = qed_vf_pf_txq_start(p_hwfn, p_cid,
					 pbl_addr, pbl_size,
					 &p_ret_params->p_doorbell);

	if (rc)
		qed_eth_queue_cid_release(p_hwfn, p_cid);
	else
		p_ret_params->p_handle = (void *)p_cid;

	return rc;
}