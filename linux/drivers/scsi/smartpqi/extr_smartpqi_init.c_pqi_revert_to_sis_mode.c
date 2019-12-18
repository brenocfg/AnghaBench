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
struct pqi_ctrl_info {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_MODE_NONE ; 
 int /*<<< orphan*/  SIS_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pqi_change_irq_mode (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int pqi_reset (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_save_ctrl_mode (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int sis_reenable_sis_mode (struct pqi_ctrl_info*) ; 

__attribute__((used)) static int pqi_revert_to_sis_mode(struct pqi_ctrl_info *ctrl_info)
{
	int rc;

	pqi_change_irq_mode(ctrl_info, IRQ_MODE_NONE);
	rc = pqi_reset(ctrl_info);
	if (rc)
		return rc;
	rc = sis_reenable_sis_mode(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"re-enabling SIS mode failed with error %d\n", rc);
		return rc;
	}
	pqi_save_ctrl_mode(ctrl_info, SIS_MODE);

	return 0;
}