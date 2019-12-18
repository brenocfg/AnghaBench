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
struct pqi_ctrl_info {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTDOWN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct pqi_ctrl_info* pci_get_drvdata (struct pci_dev*) ; 
 int pqi_flush_cache (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqi_free_interrupts (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_reset (struct pqi_ctrl_info*) ; 

__attribute__((used)) static void pqi_shutdown(struct pci_dev *pci_dev)
{
	int rc;
	struct pqi_ctrl_info *ctrl_info;

	ctrl_info = pci_get_drvdata(pci_dev);
	if (!ctrl_info)
		goto error;

	/*
	 * Write all data in the controller's battery-backed cache to
	 * storage.
	 */
	rc = pqi_flush_cache(ctrl_info, SHUTDOWN);
	pqi_free_interrupts(ctrl_info);
	pqi_reset(ctrl_info);
	if (rc == 0)
		return;

error:
	dev_warn(&pci_dev->dev,
		"unable to flush controller cache\n");
}