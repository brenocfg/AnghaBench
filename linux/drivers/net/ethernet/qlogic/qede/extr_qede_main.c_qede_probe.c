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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  enum qede_pci_private { ____Placeholder_qede_pci_private } qede_pci_private ;

/* Variables and functions */
#define  QEDE_PRIVATE_VF 128 
 int /*<<< orphan*/  QEDE_PROBE_NORMAL ; 
 int QED_LOG_VERBOSE_MASK ; 
 int __qede_probe (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int debug ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qede_config_debug (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qede_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	bool is_vf = false;
	u32 dp_module = 0;
	u8 dp_level = 0;

	switch ((enum qede_pci_private)id->driver_data) {
	case QEDE_PRIVATE_VF:
		if (debug & QED_LOG_VERBOSE_MASK)
			dev_err(&pdev->dev, "Probing a VF\n");
		is_vf = true;
		break;
	default:
		if (debug & QED_LOG_VERBOSE_MASK)
			dev_err(&pdev->dev, "Probing a PF\n");
	}

	qede_config_debug(debug, &dp_module, &dp_level);

	return __qede_probe(pdev, dp_module, dp_level, is_vf,
			    QEDE_PROBE_NORMAL);
}