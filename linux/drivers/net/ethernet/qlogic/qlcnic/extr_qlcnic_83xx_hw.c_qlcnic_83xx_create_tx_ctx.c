#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int u16 ;
struct qlcnic_tx_mbx_out {size_t host_prod; int /*<<< orphan*/  state; int /*<<< orphan*/  ctx_id; } ;
struct qlcnic_tx_mbx {int intr_id; scalar_t__ src; int /*<<< orphan*/  size; void* cnsmr_index_high; void* cnsmr_index_low; void* phys_addr_high; void* phys_addr_low; } ;
struct qlcnic_host_tx_ring {size_t crb_cmd_producer; size_t crb_intr_mask; int /*<<< orphan*/  ctx_id; int /*<<< orphan*/  num_desc; int /*<<< orphan*/  hw_cons_phys_addr; int /*<<< orphan*/  phys_addr; scalar_t__* hw_consumer; scalar_t__ sw_consumer; scalar_t__ producer; } ;
struct qlcnic_hardware_context {scalar_t__ diag_test; size_t pci_base0; TYPE_3__* intr_tbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * arg; } ;
struct TYPE_4__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ rsp; TYPE_1__ req; } ;
struct qlcnic_adapter {int flags; int drv_sds_rings; int /*<<< orphan*/  netdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_6__ {int id; size_t src; } ;

/* Variables and functions */
 void* LSD (int /*<<< orphan*/ ) ; 
 void* MSD (int /*<<< orphan*/ ) ; 
 int QLCNIC_CAP0_LEGACY_CONTEXT ; 
 int /*<<< orphan*/  QLCNIC_CMD_CREATE_TX_CTX ; 
 int /*<<< orphan*/  QLCNIC_DEF_INT_ID ; 
 scalar_t__ QLCNIC_LOOPBACK_TEST ; 
 int QLCNIC_MSIX_ENABLED ; 
 size_t QLCNIC_SINGLE_RING ; 
 int QLCNIC_TX_INTR_SHARED ; 
 int QLCRDX (struct qlcnic_hardware_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (size_t*,struct qlcnic_tx_mbx*,int) ; 
 int /*<<< orphan*/  memset (struct qlcnic_tx_mbx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 int /*<<< orphan*/  qlcnic_pf_set_interface_id_create_tx_ctx (struct qlcnic_adapter*,size_t*) ; 
 scalar_t__ qlcnic_sriov_pf_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 

int qlcnic_83xx_create_tx_ctx(struct qlcnic_adapter *adapter,
			      struct qlcnic_host_tx_ring *tx, int ring)
{
	int err;
	u16 msix_id;
	u32 *buf, intr_mask, temp = 0;
	struct qlcnic_cmd_args cmd;
	struct qlcnic_tx_mbx mbx;
	struct qlcnic_tx_mbx_out *mbx_out;
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	u32 msix_vector;

	/* Reset host resources */
	tx->producer = 0;
	tx->sw_consumer = 0;
	*(tx->hw_consumer) = 0;

	memset(&mbx, 0, sizeof(struct qlcnic_tx_mbx));

	/* setup mailbox inbox registerss */
	mbx.phys_addr_low = LSD(tx->phys_addr);
	mbx.phys_addr_high = MSD(tx->phys_addr);
	mbx.cnsmr_index_low = LSD(tx->hw_cons_phys_addr);
	mbx.cnsmr_index_high = MSD(tx->hw_cons_phys_addr);
	mbx.size = tx->num_desc;
	if (adapter->flags & QLCNIC_MSIX_ENABLED) {
		if (!(adapter->flags & QLCNIC_TX_INTR_SHARED))
			msix_vector = adapter->drv_sds_rings + ring;
		else
			msix_vector = adapter->drv_sds_rings - 1;
		msix_id = ahw->intr_tbl[msix_vector].id;
	} else {
		msix_id = QLCRDX(ahw, QLCNIC_DEF_INT_ID);
	}

	if (adapter->ahw->diag_test != QLCNIC_LOOPBACK_TEST)
		mbx.intr_id = msix_id;
	else
		mbx.intr_id = 0xffff;
	mbx.src = 0;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CREATE_TX_CTX);
	if (err)
		return err;

	if (qlcnic_sriov_pf_check(adapter) || qlcnic_sriov_vf_check(adapter))
		cmd.req.arg[0] |= (0x3 << 29);

	if (qlcnic_sriov_pf_check(adapter))
		qlcnic_pf_set_interface_id_create_tx_ctx(adapter, &temp);

	cmd.req.arg[1] = QLCNIC_CAP0_LEGACY_CONTEXT;
	cmd.req.arg[5] = QLCNIC_SINGLE_RING | temp;

	buf = &cmd.req.arg[6];
	memcpy(buf, &mbx, sizeof(struct qlcnic_tx_mbx));
	/* send the mailbox command*/
	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err) {
		netdev_err(adapter->netdev,
			   "Failed to create Tx ctx in firmware 0x%x\n", err);
		goto out;
	}
	mbx_out = (struct qlcnic_tx_mbx_out *)&cmd.rsp.arg[2];
	tx->crb_cmd_producer = ahw->pci_base0 + mbx_out->host_prod;
	tx->ctx_id = mbx_out->ctx_id;
	if ((adapter->flags & QLCNIC_MSIX_ENABLED) &&
	    !(adapter->flags & QLCNIC_TX_INTR_SHARED)) {
		intr_mask = ahw->intr_tbl[adapter->drv_sds_rings + ring].src;
		tx->crb_intr_mask = ahw->pci_base0 + intr_mask;
	}
	netdev_info(adapter->netdev,
		    "Tx Context[0x%x] Created, state:0x%x\n",
		    tx->ctx_id, mbx_out->state);
out:
	qlcnic_free_mbx_args(&cmd);
	return err;
}