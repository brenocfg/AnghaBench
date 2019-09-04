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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u32 ;

/* Variables and functions */
#define  PCI_DEVICE_ID_QLOGIC_QLE824X 134 
#define  PCI_DEVICE_ID_QLOGIC_QLE834X 133 
#define  PCI_DEVICE_ID_QLOGIC_QLE844X 132 
#define  PCI_DEVICE_ID_QLOGIC_QLE8830 131 
#define  PCI_DEVICE_ID_QLOGIC_VF_QLE834X 130 
#define  PCI_DEVICE_ID_QLOGIC_VF_QLE844X 129 
#define  PCI_DEVICE_ID_QLOGIC_VF_QLE8C30 128 
 int /*<<< orphan*/  QLCNIC_82XX_BAR0_LENGTH ; 
 int /*<<< orphan*/  QLCNIC_83XX_BAR0_LENGTH ; 

__attribute__((used)) static void qlcnic_get_bar_length(u32 dev_id, ulong *bar)
{
	switch (dev_id) {
	case PCI_DEVICE_ID_QLOGIC_QLE824X:
		*bar = QLCNIC_82XX_BAR0_LENGTH;
		break;
	case PCI_DEVICE_ID_QLOGIC_QLE834X:
	case PCI_DEVICE_ID_QLOGIC_QLE8830:
	case PCI_DEVICE_ID_QLOGIC_QLE844X:
	case PCI_DEVICE_ID_QLOGIC_VF_QLE834X:
	case PCI_DEVICE_ID_QLOGIC_VF_QLE844X:
	case PCI_DEVICE_ID_QLOGIC_VF_QLE8C30:
		*bar = QLCNIC_83XX_BAR0_LENGTH;
		break;
	default:
		*bar = 0;
	}
}