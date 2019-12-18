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
typedef  int u32 ;
struct cxgbit_sock {int /*<<< orphan*/  tid; } ;
struct cxgbit_lro_pdu_cb {int flags; } ;

/* Variables and functions */
 int CPL_RX_ISCSI_DDP_STATUS_DCRC_SHIFT ; 
 int CPL_RX_ISCSI_DDP_STATUS_DDP_SHIFT ; 
 int CPL_RX_ISCSI_DDP_STATUS_HCRC_SHIFT ; 
 int CPL_RX_ISCSI_DDP_STATUS_PAD_SHIFT ; 
 int PDUCBF_RX_DATA ; 
 int PDUCBF_RX_DATA_DDPD ; 
 int PDUCBF_RX_DCRC_ERR ; 
 int PDUCBF_RX_HCRC_ERR ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cxgbit_process_ddpvld(struct cxgbit_sock *csk, struct cxgbit_lro_pdu_cb *pdu_cb,
		      u32 ddpvld)
{

	if (ddpvld & (1 << CPL_RX_ISCSI_DDP_STATUS_HCRC_SHIFT)) {
		pr_info("tid 0x%x, status 0x%x, hcrc bad.\n", csk->tid, ddpvld);
		pdu_cb->flags |= PDUCBF_RX_HCRC_ERR;
	}

	if (ddpvld & (1 << CPL_RX_ISCSI_DDP_STATUS_DCRC_SHIFT)) {
		pr_info("tid 0x%x, status 0x%x, dcrc bad.\n", csk->tid, ddpvld);
		pdu_cb->flags |= PDUCBF_RX_DCRC_ERR;
	}

	if (ddpvld & (1 << CPL_RX_ISCSI_DDP_STATUS_PAD_SHIFT))
		pr_info("tid 0x%x, status 0x%x, pad bad.\n", csk->tid, ddpvld);

	if ((ddpvld & (1 << CPL_RX_ISCSI_DDP_STATUS_DDP_SHIFT)) &&
	    (!(pdu_cb->flags & PDUCBF_RX_DATA))) {
		pdu_cb->flags |= PDUCBF_RX_DATA_DDPD;
	}
}