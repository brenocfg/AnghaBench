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
struct TYPE_4__ {struct hclge_mac mac; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector_irq; } ;
struct hclge_dev {TYPE_2__ hw; TYPE_1__ misc_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_destroy_cmd_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  hclge_enable_vector (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hclge_misc_irq_uninit (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_pci_uninit (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_state_uninit (struct hclge_dev*) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_uninit_ae_dev(struct hnae3_ae_dev *ae_dev)
{
	struct hclge_dev *hdev = ae_dev->priv;
	struct hclge_mac *mac = &hdev->hw.mac;

	hclge_state_uninit(hdev);

	if (mac->phydev)
		mdiobus_unregister(mac->mdio_bus);

	/* Disable MISC vector(vector0) */
	hclge_enable_vector(&hdev->misc_vector, false);
	synchronize_irq(hdev->misc_vector.vector_irq);

	hclge_destroy_cmd_queue(&hdev->hw);
	hclge_misc_irq_uninit(hdev);
	hclge_pci_uninit(hdev);
	ae_dev->priv = NULL;
}