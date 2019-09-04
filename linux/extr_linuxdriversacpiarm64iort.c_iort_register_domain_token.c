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
struct iort_its_msi_chip {int translation_id; int /*<<< orphan*/  list; int /*<<< orphan*/  base_addr; struct fwnode_handle* fw_node; } ;
struct fwnode_handle {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  iort_msi_chip_list ; 
 int /*<<< orphan*/  iort_msi_chip_lock ; 
 struct iort_its_msi_chip* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int iort_register_domain_token(int trans_id, phys_addr_t base,
			       struct fwnode_handle *fw_node)
{
	struct iort_its_msi_chip *its_msi_chip;

	its_msi_chip = kzalloc(sizeof(*its_msi_chip), GFP_KERNEL);
	if (!its_msi_chip)
		return -ENOMEM;

	its_msi_chip->fw_node = fw_node;
	its_msi_chip->translation_id = trans_id;
	its_msi_chip->base_addr = base;

	spin_lock(&iort_msi_chip_lock);
	list_add(&its_msi_chip->list, &iort_msi_chip_list);
	spin_unlock(&iort_msi_chip_lock);

	return 0;
}