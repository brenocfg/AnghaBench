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
struct ath10k_pci {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  chip_id; } ;
struct ath10k {TYPE_2__ bus_param; } ;
struct TYPE_3__ {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  QCA6164_2_1_DEVICE_ID 144 
#define  QCA6174_2_1_DEVICE_ID 143 
#define  QCA6174_HW_1_0_CHIP_ID_REV 142 
#define  QCA6174_HW_1_1_CHIP_ID_REV 141 
#define  QCA6174_HW_1_3_CHIP_ID_REV 140 
#define  QCA6174_HW_2_1_CHIP_ID_REV 139 
#define  QCA6174_HW_2_2_CHIP_ID_REV 138 
#define  QCA6174_HW_3_0_CHIP_ID_REV 137 
#define  QCA6174_HW_3_1_CHIP_ID_REV 136 
#define  QCA6174_HW_3_2_CHIP_ID_REV 135 
#define  QCA9377_1_0_DEVICE_ID 134 
#define  QCA9887_1_0_DEVICE_ID 133 
#define  QCA9888_2_0_DEVICE_ID 132 
#define  QCA988X_2_0_DEVICE_ID 131 
#define  QCA988X_2_0_DEVICE_ID_UBNT 130 
#define  QCA9984_1_0_DEVICE_ID 129 
#define  QCA99X0_2_0_DEVICE_ID 128 
 int /*<<< orphan*/  SOC_CHIP_ID_REV ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 

__attribute__((used)) static int ath10k_pci_get_num_banks(struct ath10k *ar)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	switch (ar_pci->pdev->device) {
	case QCA988X_2_0_DEVICE_ID_UBNT:
	case QCA988X_2_0_DEVICE_ID:
	case QCA99X0_2_0_DEVICE_ID:
	case QCA9888_2_0_DEVICE_ID:
	case QCA9984_1_0_DEVICE_ID:
	case QCA9887_1_0_DEVICE_ID:
		return 1;
	case QCA6164_2_1_DEVICE_ID:
	case QCA6174_2_1_DEVICE_ID:
		switch (MS(ar->bus_param.chip_id, SOC_CHIP_ID_REV)) {
		case QCA6174_HW_1_0_CHIP_ID_REV:
		case QCA6174_HW_1_1_CHIP_ID_REV:
		case QCA6174_HW_2_1_CHIP_ID_REV:
		case QCA6174_HW_2_2_CHIP_ID_REV:
			return 3;
		case QCA6174_HW_1_3_CHIP_ID_REV:
			return 2;
		case QCA6174_HW_3_0_CHIP_ID_REV:
		case QCA6174_HW_3_1_CHIP_ID_REV:
		case QCA6174_HW_3_2_CHIP_ID_REV:
			return 9;
		}
		break;
	case QCA9377_1_0_DEVICE_ID:
		return 9;
	}

	ath10k_warn(ar, "unknown number of banks, assuming 1\n");
	return 1;
}