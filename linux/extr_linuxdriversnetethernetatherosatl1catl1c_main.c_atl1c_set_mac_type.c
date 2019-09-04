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
struct atl1c_hw {int device_id; int /*<<< orphan*/  nic_type; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_ATHEROS_L1D 133 
#define  PCI_DEVICE_ID_ATHEROS_L1D_2_0 132 
#define  PCI_DEVICE_ID_ATHEROS_L2C_B 131 
#define  PCI_DEVICE_ID_ATHEROS_L2C_B2 130 
#define  PCI_DEVICE_ID_ATTANSIC_L1C 129 
#define  PCI_DEVICE_ID_ATTANSIC_L2C 128 
 int /*<<< orphan*/  athr_l1c ; 
 int /*<<< orphan*/  athr_l1d ; 
 int /*<<< orphan*/  athr_l1d_2 ; 
 int /*<<< orphan*/  athr_l2c ; 
 int /*<<< orphan*/  athr_l2c_b ; 
 int /*<<< orphan*/  athr_l2c_b2 ; 

__attribute__((used)) static void atl1c_set_mac_type(struct atl1c_hw *hw)
{
	switch (hw->device_id) {
	case PCI_DEVICE_ID_ATTANSIC_L2C:
		hw->nic_type = athr_l2c;
		break;
	case PCI_DEVICE_ID_ATTANSIC_L1C:
		hw->nic_type = athr_l1c;
		break;
	case PCI_DEVICE_ID_ATHEROS_L2C_B:
		hw->nic_type = athr_l2c_b;
		break;
	case PCI_DEVICE_ID_ATHEROS_L2C_B2:
		hw->nic_type = athr_l2c_b2;
		break;
	case PCI_DEVICE_ID_ATHEROS_L1D:
		hw->nic_type = athr_l1d;
		break;
	case PCI_DEVICE_ID_ATHEROS_L1D_2_0:
		hw->nic_type = athr_l1d_2;
		break;
	default:
		break;
	}
}