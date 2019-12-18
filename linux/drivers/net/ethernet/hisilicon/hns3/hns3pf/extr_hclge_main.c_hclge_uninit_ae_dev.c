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
struct hnae3_ae_dev {struct hclge_dev* priv; } ;
struct hclge_mac {int /*<<< orphan*/  mdio_bus; scalar_t__ phydev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector_irq; } ;
struct TYPE_3__ {struct hclge_mac mac; } ;
struct hclge_dev {int /*<<< orphan*/  vport_cfg_mutex; int /*<<< orphan*/  vport_lock; TYPE_2__ misc_vector; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_cmd_uninit (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_config_mac_tnl_int (struct hclge_dev*,int) ; 
 int /*<<< orphan*/  hclge_config_nic_hw_error (struct hclge_dev*,int) ; 
 int /*<<< orphan*/  hclge_config_rocee_ras_interrupt (struct hclge_dev*,int) ; 
 int /*<<< orphan*/  hclge_enable_vector (TYPE_2__*,int) ; 
 int /*<<< orphan*/  hclge_misc_affinity_teardown (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_misc_irq_uninit (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_pci_uninit (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_state_uninit (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_uninit_umv_space (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_uninit_vport_mac_table (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_uninit_vport_vlan_table (struct hclge_dev*) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_uninit_ae_dev(struct hnae3_ae_dev *ae_dev)
{
	struct hclge_dev *hdev = ae_dev->priv;
	struct hclge_mac *mac = &hdev->hw.mac;

	hclge_misc_affinity_teardown(hdev);
	hclge_state_uninit(hdev);

	if (mac->phydev)
		mdiobus_unregister(mac->mdio_bus);

	hclge_uninit_umv_space(hdev);

	/* Disable MISC vector(vector0) */
	hclge_enable_vector(&hdev->misc_vector, false);
	synchronize_irq(hdev->misc_vector.vector_irq);

	/* Disable all hw interrupts */
	hclge_config_mac_tnl_int(hdev, false);
	hclge_config_nic_hw_error(hdev, false);
	hclge_config_rocee_ras_interrupt(hdev, false);

	hclge_cmd_uninit(hdev);
	hclge_misc_irq_uninit(hdev);
	hclge_pci_uninit(hdev);
	mutex_destroy(&hdev->vport_lock);
	hclge_uninit_vport_mac_table(hdev);
	hclge_uninit_vport_vlan_table(hdev);
	mutex_destroy(&hdev->vport_cfg_mutex);
	ae_dev->priv = NULL;
}