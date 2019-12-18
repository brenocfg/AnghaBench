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
struct pqi_ctrl_info {int in_shutdown; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct pqi_ctrl_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pqi_remove_ctrl (struct pqi_ctrl_info*) ; 

__attribute__((used)) static void pqi_pci_remove(struct pci_dev *pci_dev)
{
	struct pqi_ctrl_info *ctrl_info;

	ctrl_info = pci_get_drvdata(pci_dev);
	if (!ctrl_info)
		return;

	ctrl_info->in_shutdown = true;

	pqi_remove_ctrl(ctrl_info);
}