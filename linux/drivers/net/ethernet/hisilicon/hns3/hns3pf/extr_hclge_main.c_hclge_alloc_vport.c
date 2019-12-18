#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int rx_vlan_offload_en; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct hclge_vport {int vport_id; int /*<<< orphan*/  mc_mac_list; int /*<<< orphan*/  uc_mac_list; int /*<<< orphan*/  vlan_list; TYPE_2__ rxvlan_cfg; TYPE_1__ port_base_vlan_cfg; int /*<<< orphan*/  mps; struct hclge_dev* back; } ;
struct hclge_dev {int num_vmdq_vport; int num_req_vfs; int num_tqps; int num_alloc_vport; int num_alloc_vfs; struct hclge_vport* vport; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_IOV ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCLGE_MAC_DEFAULT_FRAME ; 
 int /*<<< orphan*/  HNAE3_PORT_BASE_VLAN_DISABLE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 struct hclge_vport* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int hclge_vport_setup (struct hclge_vport*,int) ; 

__attribute__((used)) static int hclge_alloc_vport(struct hclge_dev *hdev)
{
	struct pci_dev *pdev = hdev->pdev;
	struct hclge_vport *vport;
	u32 tqp_main_vport;
	u32 tqp_per_vport;
	int num_vport, i;
	int ret;

	/* We need to alloc a vport for main NIC of PF */
	num_vport = hdev->num_vmdq_vport + hdev->num_req_vfs + 1;

	if (hdev->num_tqps < num_vport) {
		dev_err(&hdev->pdev->dev, "tqps(%d) is less than vports(%d)",
			hdev->num_tqps, num_vport);
		return -EINVAL;
	}

	/* Alloc the same number of TQPs for every vport */
	tqp_per_vport = hdev->num_tqps / num_vport;
	tqp_main_vport = tqp_per_vport + hdev->num_tqps % num_vport;

	vport = devm_kcalloc(&pdev->dev, num_vport, sizeof(struct hclge_vport),
			     GFP_KERNEL);
	if (!vport)
		return -ENOMEM;

	hdev->vport = vport;
	hdev->num_alloc_vport = num_vport;

	if (IS_ENABLED(CONFIG_PCI_IOV))
		hdev->num_alloc_vfs = hdev->num_req_vfs;

	for (i = 0; i < num_vport; i++) {
		vport->back = hdev;
		vport->vport_id = i;
		vport->mps = HCLGE_MAC_DEFAULT_FRAME;
		vport->port_base_vlan_cfg.state = HNAE3_PORT_BASE_VLAN_DISABLE;
		vport->rxvlan_cfg.rx_vlan_offload_en = true;
		INIT_LIST_HEAD(&vport->vlan_list);
		INIT_LIST_HEAD(&vport->uc_mac_list);
		INIT_LIST_HEAD(&vport->mc_mac_list);

		if (i == 0)
			ret = hclge_vport_setup(vport, tqp_main_vport);
		else
			ret = hclge_vport_setup(vport, tqp_per_vport);
		if (ret) {
			dev_err(&pdev->dev,
				"vport setup failed for vport %d, %d\n",
				i, ret);
			return ret;
		}

		vport++;
	}

	return 0;
}