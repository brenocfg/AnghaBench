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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct aq_nic_cfg_s {size_t irq_type; unsigned int vecs; TYPE_3__* aq_hw_caps; int /*<<< orphan*/  aq_rss; int /*<<< orphan*/  link_speed_msk; } ;
struct TYPE_4__ {scalar_t__ mbps; } ;
struct aq_hw_s {TYPE_2__* aq_fw_ops; TYPE_1__ aq_link_status; struct aq_nic_cfg_s* aq_nic_cfg; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* update_stats ) (struct aq_hw_s*) ;int /*<<< orphan*/  (* set_state ) (struct aq_hw_s*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_link_speed ) (struct aq_hw_s*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int HW_ATL_B0_ERR_INT ; 
 int /*<<< orphan*/  HW_ATL_PCI_REG_CONTROL6_ADR ; 
 int /*<<< orphan*/  HW_ATL_TX_DMA_TOTAL_REQ_LIMIT_ADR ; 
 int /*<<< orphan*/  MPI_INIT ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int aq_hw_read_reg (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_hw_write_reg (struct aq_hw_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_atl_b0_hw_init_rx_path (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_b0_hw_init_tx_path (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_b0_hw_mac_addr_set (struct aq_hw_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_atl_b0_hw_offload_set (struct aq_hw_s*,struct aq_nic_cfg_s*) ; 
 int /*<<< orphan*/  hw_atl_b0_hw_qos_set (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_b0_hw_rss_hash_set (struct aq_hw_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_atl_b0_hw_rss_set (struct aq_hw_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_atl_itr_irq_auto_masklsw_set (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_reg_gen_irq_map_set (struct aq_hw_s*,int,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_reg_irq_glb_ctl_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  stub1 (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct aq_hw_s*) ; 

__attribute__((used)) static int hw_atl_b0_hw_init(struct aq_hw_s *self, u8 *mac_addr)
{
	static u32 aq_hw_atl_igcr_table_[4][2] = {
		{ 0x20000000U, 0x20000000U }, /* AQ_IRQ_INVALID */
		{ 0x20000080U, 0x20000080U }, /* AQ_IRQ_LEGACY */
		{ 0x20000021U, 0x20000025U }, /* AQ_IRQ_MSI */
		{ 0x20000022U, 0x20000026U }  /* AQ_IRQ_MSIX */
	};

	int err = 0;
	u32 val;

	struct aq_nic_cfg_s *aq_nic_cfg = self->aq_nic_cfg;

	hw_atl_b0_hw_init_tx_path(self);
	hw_atl_b0_hw_init_rx_path(self);

	hw_atl_b0_hw_mac_addr_set(self, mac_addr);

	self->aq_fw_ops->set_link_speed(self, aq_nic_cfg->link_speed_msk);
	self->aq_fw_ops->set_state(self, MPI_INIT);

	hw_atl_b0_hw_qos_set(self);
	hw_atl_b0_hw_rss_set(self, &aq_nic_cfg->aq_rss);
	hw_atl_b0_hw_rss_hash_set(self, &aq_nic_cfg->aq_rss);

	/* Force limit MRRS on RDM/TDM to 2K */
	val = aq_hw_read_reg(self, HW_ATL_PCI_REG_CONTROL6_ADR);
	aq_hw_write_reg(self, HW_ATL_PCI_REG_CONTROL6_ADR,
			(val & ~0x707) | 0x404);

	/* TX DMA total request limit. B0 hardware is not capable to
	 * handle more than (8K-MRRS) incoming DMA data.
	 * Value 24 in 256byte units
	 */
	aq_hw_write_reg(self, HW_ATL_TX_DMA_TOTAL_REQ_LIMIT_ADR, 24);

	/* Reset link status and read out initial hardware counters */
	self->aq_link_status.mbps = 0;
	self->aq_fw_ops->update_stats(self);

	err = aq_hw_err_from_flags(self);
	if (err < 0)
		goto err_exit;

	/* Interrupts */
	hw_atl_reg_irq_glb_ctl_set(self,
				   aq_hw_atl_igcr_table_[aq_nic_cfg->irq_type]
						 [(aq_nic_cfg->vecs > 1U) ?
						 1 : 0]);

	hw_atl_itr_irq_auto_masklsw_set(self, aq_nic_cfg->aq_hw_caps->irq_mask);

	/* Interrupts */
	hw_atl_reg_gen_irq_map_set(self,
				   ((HW_ATL_B0_ERR_INT << 0x18) | (1U << 0x1F)) |
			    ((HW_ATL_B0_ERR_INT << 0x10) | (1U << 0x17)), 0U);

	hw_atl_b0_hw_offload_set(self, aq_nic_cfg);

err_exit:
	return err;
}