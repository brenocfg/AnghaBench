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
struct cx23885_dev {int board; int /*<<< orphan*/ * sd_ir; } ;

/* Variables and functions */
#define  CX23885_BOARD_DVBSKY_S950 143 
#define  CX23885_BOARD_DVBSKY_S950C 142 
#define  CX23885_BOARD_DVBSKY_S952 141 
#define  CX23885_BOARD_DVBSKY_T9580 140 
#define  CX23885_BOARD_DVBSKY_T980C 139 
#define  CX23885_BOARD_DVBSKY_T982 138 
#define  CX23885_BOARD_HAUPPAUGE_HVR1250 137 
#define  CX23885_BOARD_HAUPPAUGE_HVR1270 136 
#define  CX23885_BOARD_HAUPPAUGE_HVR1290 135 
#define  CX23885_BOARD_HAUPPAUGE_HVR1850 134 
#define  CX23885_BOARD_MYGICA_X8507 133 
#define  CX23885_BOARD_TBS_6980 132 
#define  CX23885_BOARD_TBS_6981 131 
#define  CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL 130 
#define  CX23885_BOARD_TEVII_S470 129 
#define  CX23885_BOARD_TT_CT2_4500_CI 128 
 int /*<<< orphan*/  PCI_MSK_AV_CORE ; 
 int /*<<< orphan*/  PCI_MSK_IR ; 
 int /*<<< orphan*/  cx23885_irq_remove (struct cx23885_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx23888_ir_remove (struct cx23885_dev*) ; 

void cx23885_ir_fini(struct cx23885_dev *dev)
{
	switch (dev->board) {
	case CX23885_BOARD_HAUPPAUGE_HVR1270:
	case CX23885_BOARD_HAUPPAUGE_HVR1850:
	case CX23885_BOARD_HAUPPAUGE_HVR1290:
		cx23885_irq_remove(dev, PCI_MSK_IR);
		cx23888_ir_remove(dev);
		dev->sd_ir = NULL;
		break;
	case CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL:
	case CX23885_BOARD_TEVII_S470:
	case CX23885_BOARD_HAUPPAUGE_HVR1250:
	case CX23885_BOARD_MYGICA_X8507:
	case CX23885_BOARD_TBS_6980:
	case CX23885_BOARD_TBS_6981:
	case CX23885_BOARD_DVBSKY_T9580:
	case CX23885_BOARD_DVBSKY_T980C:
	case CX23885_BOARD_DVBSKY_S950C:
	case CX23885_BOARD_TT_CT2_4500_CI:
	case CX23885_BOARD_DVBSKY_S950:
	case CX23885_BOARD_DVBSKY_S952:
	case CX23885_BOARD_DVBSKY_T982:
		cx23885_irq_remove(dev, PCI_MSK_AV_CORE);
		/* sd_ir is a duplicate pointer to the AV Core, just clear it */
		dev->sd_ir = NULL;
		break;
	}
}