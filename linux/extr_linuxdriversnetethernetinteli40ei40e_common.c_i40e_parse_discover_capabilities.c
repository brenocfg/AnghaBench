#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct i40e_hw_capabilities {int switch_mode; int management_mode; int mng_protocols_over_mctp; int npar_enable; int os2bmc; int valid_functions; int sr_iov_1_1; int num_vfs; int vf_base_id; int vmdq; int evb_802_1_qbg; int evb_802_1_qbh; int num_vsis; int dcb; int enabled_tcmap; int maxtc; int fcoe; int iscsi; int rss; int rss_table_size; int rss_table_entry_width; int num_rx_qp; int base_queue; int num_tx_qp; int num_msix_vectors; int num_msix_vectors_vf; int flex10_enable; int flex10_capable; int flex10_mode; int flex10_status; int mgmt_cem; int iwarp; int* led; int* sdp; int mdio_port_num; int mdio_port_mode; int ieee_1588; int fd; int fd_filters_guaranteed; int fd_filters_best_effort; int wr_csr_prot; int sec_rev_disabled; int update_disabled; int /*<<< orphan*/  rx_buf_chain_len; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct i40e_hw {int num_ports; int partition_id; int pf_id; int num_partitions; TYPE_1__ mac; struct i40e_hw_capabilities func_caps; struct i40e_hw_capabilities dev_caps; } ;
struct i40e_aqc_list_capabilities_element_resp {int major_rev; int /*<<< orphan*/  phys_id; int /*<<< orphan*/  logical_id; int /*<<< orphan*/  number; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  ocp_cfg_word0 ;
typedef  int /*<<< orphan*/  i40e_status ;
typedef  enum i40e_admin_queue_opc { ____Placeholder_i40e_admin_queue_opc } i40e_admin_queue_opc ;

/* Variables and functions */
#define  I40E_AQ_CAP_ID_1588 156 
#define  I40E_AQ_CAP_ID_8021QBG 155 
#define  I40E_AQ_CAP_ID_8021QBR 154 
#define  I40E_AQ_CAP_ID_CEM 153 
#define  I40E_AQ_CAP_ID_DCB 152 
#define  I40E_AQ_CAP_ID_FCOE 151 
#define  I40E_AQ_CAP_ID_FLEX10 150 
#define  I40E_AQ_CAP_ID_FLOW_DIRECTOR 149 
#define  I40E_AQ_CAP_ID_FUNCTIONS_VALID 148 
#define  I40E_AQ_CAP_ID_ISCSI 147 
#define  I40E_AQ_CAP_ID_IWARP 146 
#define  I40E_AQ_CAP_ID_LED 145 
#define  I40E_AQ_CAP_ID_MDIO 144 
#define  I40E_AQ_CAP_ID_MNG_MODE 143 
#define  I40E_AQ_CAP_ID_MSIX 142 
#define  I40E_AQ_CAP_ID_NPAR_ACTIVE 141 
#define  I40E_AQ_CAP_ID_NVM_MGMT 140 
#define  I40E_AQ_CAP_ID_OS2BMC_CAP 139 
#define  I40E_AQ_CAP_ID_RSS 138 
#define  I40E_AQ_CAP_ID_RXQ 137 
#define  I40E_AQ_CAP_ID_SDP 136 
#define  I40E_AQ_CAP_ID_SRIOV 135 
#define  I40E_AQ_CAP_ID_SWITCH_MODE 134 
#define  I40E_AQ_CAP_ID_TXQ 133 
#define  I40E_AQ_CAP_ID_VF 132 
#define  I40E_AQ_CAP_ID_VF_MSIX 131 
#define  I40E_AQ_CAP_ID_VMDQ 130 
#define  I40E_AQ_CAP_ID_VSI 129 
#define  I40E_AQ_CAP_ID_WSR_PROT 128 
 int /*<<< orphan*/  I40E_DEBUG_ALL ; 
 int /*<<< orphan*/  I40E_DEBUG_INIT ; 
 int I40E_HW_CAP_MAX_GPIO ; 
 scalar_t__ I40E_MAC_X722 ; 
 int /*<<< orphan*/  I40E_MAX_CHAINED_RX_BUFFERS ; 
 int I40E_NVM_MGMT_SEC_REV_DISABLED ; 
 int I40E_NVM_MGMT_UPDATE_DISABLED ; 
 int I40E_PRTGEN_CNF ; 
 int I40E_PRTGEN_CNF_PORT_DIS_MASK ; 
 int /*<<< orphan*/  I40E_RESOURCE_READ ; 
 int /*<<< orphan*/  I40E_SR_EMP_MODULE_PTR ; 
 int I40E_SR_OCP_CFG_WORD0 ; 
 int I40E_SR_OCP_ENABLED ; 
 int /*<<< orphan*/  i40e_acquire_nvm (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aq_debug_read_register (struct i40e_hw*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_read_nvm (struct i40e_hw*,int /*<<< orphan*/ ,int,int,int*,int,int /*<<< orphan*/ *) ; 
 int i40e_aqc_opc_list_dev_capabilities ; 
 int i40e_aqc_opc_list_func_capabilities ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  i40e_release_nvm (struct i40e_hw*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_parse_discover_capabilities(struct i40e_hw *hw, void *buff,
				     u32 cap_count,
				     enum i40e_admin_queue_opc list_type_opc)
{
	struct i40e_aqc_list_capabilities_element_resp *cap;
	u32 valid_functions, num_functions;
	u32 number, logical_id, phys_id;
	struct i40e_hw_capabilities *p;
	u16 id, ocp_cfg_word0;
	i40e_status status;
	u8 major_rev;
	u32 i = 0;

	cap = (struct i40e_aqc_list_capabilities_element_resp *) buff;

	if (list_type_opc == i40e_aqc_opc_list_dev_capabilities)
		p = &hw->dev_caps;
	else if (list_type_opc == i40e_aqc_opc_list_func_capabilities)
		p = &hw->func_caps;
	else
		return;

	for (i = 0; i < cap_count; i++, cap++) {
		id = le16_to_cpu(cap->id);
		number = le32_to_cpu(cap->number);
		logical_id = le32_to_cpu(cap->logical_id);
		phys_id = le32_to_cpu(cap->phys_id);
		major_rev = cap->major_rev;

		switch (id) {
		case I40E_AQ_CAP_ID_SWITCH_MODE:
			p->switch_mode = number;
			break;
		case I40E_AQ_CAP_ID_MNG_MODE:
			p->management_mode = number;
			if (major_rev > 1) {
				p->mng_protocols_over_mctp = logical_id;
				i40e_debug(hw, I40E_DEBUG_INIT,
					   "HW Capability: Protocols over MCTP = %d\n",
					   p->mng_protocols_over_mctp);
			} else {
				p->mng_protocols_over_mctp = 0;
			}
			break;
		case I40E_AQ_CAP_ID_NPAR_ACTIVE:
			p->npar_enable = number;
			break;
		case I40E_AQ_CAP_ID_OS2BMC_CAP:
			p->os2bmc = number;
			break;
		case I40E_AQ_CAP_ID_FUNCTIONS_VALID:
			p->valid_functions = number;
			break;
		case I40E_AQ_CAP_ID_SRIOV:
			if (number == 1)
				p->sr_iov_1_1 = true;
			break;
		case I40E_AQ_CAP_ID_VF:
			p->num_vfs = number;
			p->vf_base_id = logical_id;
			break;
		case I40E_AQ_CAP_ID_VMDQ:
			if (number == 1)
				p->vmdq = true;
			break;
		case I40E_AQ_CAP_ID_8021QBG:
			if (number == 1)
				p->evb_802_1_qbg = true;
			break;
		case I40E_AQ_CAP_ID_8021QBR:
			if (number == 1)
				p->evb_802_1_qbh = true;
			break;
		case I40E_AQ_CAP_ID_VSI:
			p->num_vsis = number;
			break;
		case I40E_AQ_CAP_ID_DCB:
			if (number == 1) {
				p->dcb = true;
				p->enabled_tcmap = logical_id;
				p->maxtc = phys_id;
			}
			break;
		case I40E_AQ_CAP_ID_FCOE:
			if (number == 1)
				p->fcoe = true;
			break;
		case I40E_AQ_CAP_ID_ISCSI:
			if (number == 1)
				p->iscsi = true;
			break;
		case I40E_AQ_CAP_ID_RSS:
			p->rss = true;
			p->rss_table_size = number;
			p->rss_table_entry_width = logical_id;
			break;
		case I40E_AQ_CAP_ID_RXQ:
			p->num_rx_qp = number;
			p->base_queue = phys_id;
			break;
		case I40E_AQ_CAP_ID_TXQ:
			p->num_tx_qp = number;
			p->base_queue = phys_id;
			break;
		case I40E_AQ_CAP_ID_MSIX:
			p->num_msix_vectors = number;
			i40e_debug(hw, I40E_DEBUG_INIT,
				   "HW Capability: MSIX vector count = %d\n",
				   p->num_msix_vectors);
			break;
		case I40E_AQ_CAP_ID_VF_MSIX:
			p->num_msix_vectors_vf = number;
			break;
		case I40E_AQ_CAP_ID_FLEX10:
			if (major_rev == 1) {
				if (number == 1) {
					p->flex10_enable = true;
					p->flex10_capable = true;
				}
			} else {
				/* Capability revision >= 2 */
				if (number & 1)
					p->flex10_enable = true;
				if (number & 2)
					p->flex10_capable = true;
			}
			p->flex10_mode = logical_id;
			p->flex10_status = phys_id;
			break;
		case I40E_AQ_CAP_ID_CEM:
			if (number == 1)
				p->mgmt_cem = true;
			break;
		case I40E_AQ_CAP_ID_IWARP:
			if (number == 1)
				p->iwarp = true;
			break;
		case I40E_AQ_CAP_ID_LED:
			if (phys_id < I40E_HW_CAP_MAX_GPIO)
				p->led[phys_id] = true;
			break;
		case I40E_AQ_CAP_ID_SDP:
			if (phys_id < I40E_HW_CAP_MAX_GPIO)
				p->sdp[phys_id] = true;
			break;
		case I40E_AQ_CAP_ID_MDIO:
			if (number == 1) {
				p->mdio_port_num = phys_id;
				p->mdio_port_mode = logical_id;
			}
			break;
		case I40E_AQ_CAP_ID_1588:
			if (number == 1)
				p->ieee_1588 = true;
			break;
		case I40E_AQ_CAP_ID_FLOW_DIRECTOR:
			p->fd = true;
			p->fd_filters_guaranteed = number;
			p->fd_filters_best_effort = logical_id;
			break;
		case I40E_AQ_CAP_ID_WSR_PROT:
			p->wr_csr_prot = (u64)number;
			p->wr_csr_prot |= (u64)logical_id << 32;
			break;
		case I40E_AQ_CAP_ID_NVM_MGMT:
			if (number & I40E_NVM_MGMT_SEC_REV_DISABLED)
				p->sec_rev_disabled = true;
			if (number & I40E_NVM_MGMT_UPDATE_DISABLED)
				p->update_disabled = true;
			break;
		default:
			break;
		}
	}

	if (p->fcoe)
		i40e_debug(hw, I40E_DEBUG_ALL, "device is FCoE capable\n");

	/* Software override ensuring FCoE is disabled if npar or mfp
	 * mode because it is not supported in these modes.
	 */
	if (p->npar_enable || p->flex10_enable)
		p->fcoe = false;

	/* count the enabled ports (aka the "not disabled" ports) */
	hw->num_ports = 0;
	for (i = 0; i < 4; i++) {
		u32 port_cfg_reg = I40E_PRTGEN_CNF + (4 * i);
		u64 port_cfg = 0;

		/* use AQ read to get the physical register offset instead
		 * of the port relative offset
		 */
		i40e_aq_debug_read_register(hw, port_cfg_reg, &port_cfg, NULL);
		if (!(port_cfg & I40E_PRTGEN_CNF_PORT_DIS_MASK))
			hw->num_ports++;
	}

	/* OCP cards case: if a mezz is removed the Ethernet port is at
	 * disabled state in PRTGEN_CNF register. Additional NVM read is
	 * needed in order to check if we are dealing with OCP card.
	 * Those cards have 4 PFs at minimum, so using PRTGEN_CNF for counting
	 * physical ports results in wrong partition id calculation and thus
	 * not supporting WoL.
	 */
	if (hw->mac.type == I40E_MAC_X722) {
		if (!i40e_acquire_nvm(hw, I40E_RESOURCE_READ)) {
			status = i40e_aq_read_nvm(hw, I40E_SR_EMP_MODULE_PTR,
						  2 * I40E_SR_OCP_CFG_WORD0,
						  sizeof(ocp_cfg_word0),
						  &ocp_cfg_word0, true, NULL);
			if (!status &&
			    (ocp_cfg_word0 & I40E_SR_OCP_ENABLED))
				hw->num_ports = 4;
			i40e_release_nvm(hw);
		}
	}

	valid_functions = p->valid_functions;
	num_functions = 0;
	while (valid_functions) {
		if (valid_functions & 1)
			num_functions++;
		valid_functions >>= 1;
	}

	/* partition id is 1-based, and functions are evenly spread
	 * across the ports as partitions
	 */
	if (hw->num_ports != 0) {
		hw->partition_id = (hw->pf_id / hw->num_ports) + 1;
		hw->num_partitions = num_functions / hw->num_ports;
	}

	/* additional HW specific goodies that might
	 * someday be HW version specific
	 */
	p->rx_buf_chain_len = I40E_MAX_CHAINED_RX_BUFFERS;
}