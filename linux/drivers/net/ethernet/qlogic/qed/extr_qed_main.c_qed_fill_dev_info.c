#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ tun_cls; scalar_t__ b_mode_enabled; } ;
struct TYPE_10__ {scalar_t__ tun_cls; scalar_t__ b_mode_enabled; } ;
struct TYPE_9__ {scalar_t__ tun_cls; scalar_t__ b_mode_enabled; } ;
struct TYPE_8__ {scalar_t__ tun_cls; scalar_t__ b_mode_enabled; } ;
struct TYPE_7__ {scalar_t__ tun_cls; scalar_t__ b_mode_enabled; } ;
struct qed_tunnel_info {TYPE_5__ ip_geneve; TYPE_4__ l2_geneve; TYPE_3__ ip_gre; TYPE_2__ l2_gre; TYPE_1__ vxlan; } ;
struct qed_ptt {int dummy; } ;
struct qed_hw_info {scalar_t__ b_wol_support; int /*<<< orphan*/  mtu; int /*<<< orphan*/  hw_mac_addr; } ;
struct qed_hwfn {int /*<<< orphan*/  abs_pf_id; struct qed_hw_info hw_info; } ;
struct qed_dev_info {int vxlan_enable; int gre_enable; int geneve_enable; int tx_switching; int wol_support; int /*<<< orphan*/  mtu; int /*<<< orphan*/  mfw_rev; int /*<<< orphan*/  flash_size; int /*<<< orphan*/  mbi_version; int /*<<< orphan*/  fw_eng; int /*<<< orphan*/  fw_rev; int /*<<< orphan*/  fw_minor; int /*<<< orphan*/  fw_major; int /*<<< orphan*/  abs_pf_id; int /*<<< orphan*/  smart_an; int /*<<< orphan*/  b_inter_pf_switch; int /*<<< orphan*/  hw_mac; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  rdma_supported; int /*<<< orphan*/  pci_irq; int /*<<< orphan*/  pci_mem_end; int /*<<< orphan*/  pci_mem_start; int /*<<< orphan*/  num_hwfns; } ;
struct TYPE_12__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  mem_end; int /*<<< orphan*/  mem_start; } ;
struct qed_dev {int /*<<< orphan*/ * hwfns; int /*<<< orphan*/  mf_bits; int /*<<< orphan*/  type; TYPE_6__ pci_params; int /*<<< orphan*/  num_hwfns; struct qed_tunnel_info tunnel; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_ENGINEERING_VERSION ; 
 int /*<<< orphan*/  FW_MAJOR_VERSION ; 
 int /*<<< orphan*/  FW_MINOR_VERSION ; 
 int /*<<< orphan*/  FW_REVISION_VERSION ; 
 scalar_t__ IS_PF (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_IS_RDMA_PERSONALITY (struct qed_hwfn*) ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_MF_INTER_PF_SWITCH ; 
 scalar_t__ QED_TUNN_CLSS_MAC_VLAN ; 
 scalar_t__ QED_WOL_SUPPORT_PME ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qed_dev_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_mcp_get_flash_size (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_mcp_get_mbi_ver (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_mcp_get_mfw_ver (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_mcp_is_smart_an_supported (struct qed_hwfn*) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_vf_get_fw_version (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qed_fill_dev_info(struct qed_dev *cdev,
		      struct qed_dev_info *dev_info)
{
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	struct qed_hw_info *hw_info = &p_hwfn->hw_info;
	struct qed_tunnel_info *tun = &cdev->tunnel;
	struct qed_ptt  *ptt;

	memset(dev_info, 0, sizeof(struct qed_dev_info));

	if (tun->vxlan.tun_cls == QED_TUNN_CLSS_MAC_VLAN &&
	    tun->vxlan.b_mode_enabled)
		dev_info->vxlan_enable = true;

	if (tun->l2_gre.b_mode_enabled && tun->ip_gre.b_mode_enabled &&
	    tun->l2_gre.tun_cls == QED_TUNN_CLSS_MAC_VLAN &&
	    tun->ip_gre.tun_cls == QED_TUNN_CLSS_MAC_VLAN)
		dev_info->gre_enable = true;

	if (tun->l2_geneve.b_mode_enabled && tun->ip_geneve.b_mode_enabled &&
	    tun->l2_geneve.tun_cls == QED_TUNN_CLSS_MAC_VLAN &&
	    tun->ip_geneve.tun_cls == QED_TUNN_CLSS_MAC_VLAN)
		dev_info->geneve_enable = true;

	dev_info->num_hwfns = cdev->num_hwfns;
	dev_info->pci_mem_start = cdev->pci_params.mem_start;
	dev_info->pci_mem_end = cdev->pci_params.mem_end;
	dev_info->pci_irq = cdev->pci_params.irq;
	dev_info->rdma_supported = QED_IS_RDMA_PERSONALITY(p_hwfn);
	dev_info->dev_type = cdev->type;
	ether_addr_copy(dev_info->hw_mac, hw_info->hw_mac_addr);

	if (IS_PF(cdev)) {
		dev_info->fw_major = FW_MAJOR_VERSION;
		dev_info->fw_minor = FW_MINOR_VERSION;
		dev_info->fw_rev = FW_REVISION_VERSION;
		dev_info->fw_eng = FW_ENGINEERING_VERSION;
		dev_info->b_inter_pf_switch = test_bit(QED_MF_INTER_PF_SWITCH,
						       &cdev->mf_bits);
		dev_info->tx_switching = true;

		if (hw_info->b_wol_support == QED_WOL_SUPPORT_PME)
			dev_info->wol_support = true;

		dev_info->smart_an = qed_mcp_is_smart_an_supported(p_hwfn);

		dev_info->abs_pf_id = QED_LEADING_HWFN(cdev)->abs_pf_id;
	} else {
		qed_vf_get_fw_version(&cdev->hwfns[0], &dev_info->fw_major,
				      &dev_info->fw_minor, &dev_info->fw_rev,
				      &dev_info->fw_eng);
	}

	if (IS_PF(cdev)) {
		ptt = qed_ptt_acquire(QED_LEADING_HWFN(cdev));
		if (ptt) {
			qed_mcp_get_mfw_ver(QED_LEADING_HWFN(cdev), ptt,
					    &dev_info->mfw_rev, NULL);

			qed_mcp_get_mbi_ver(QED_LEADING_HWFN(cdev), ptt,
					    &dev_info->mbi_version);

			qed_mcp_get_flash_size(QED_LEADING_HWFN(cdev), ptt,
					       &dev_info->flash_size);

			qed_ptt_release(QED_LEADING_HWFN(cdev), ptt);
		}
	} else {
		qed_mcp_get_mfw_ver(QED_LEADING_HWFN(cdev), NULL,
				    &dev_info->mfw_rev, NULL);
	}

	dev_info->mtu = hw_info->mtu;

	return 0;
}