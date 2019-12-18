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
struct pci_dev {int device; } ;

/* Variables and functions */
#define  E1000_DEV_ID_82540EM 148 
#define  E1000_DEV_ID_82540EM_LOM 147 
#define  E1000_DEV_ID_82540EP 146 
#define  E1000_DEV_ID_82540EP_LOM 145 
#define  E1000_DEV_ID_82540EP_LP 144 
#define  E1000_DEV_ID_82541EI 143 
#define  E1000_DEV_ID_82541EI_MOBILE 142 
#define  E1000_DEV_ID_82541ER 141 
#define  E1000_DEV_ID_82541ER_LOM 140 
#define  E1000_DEV_ID_82541GI 139 
#define  E1000_DEV_ID_82541GI_LF 138 
#define  E1000_DEV_ID_82541GI_MOBILE 137 
#define  E1000_DEV_ID_82544EI_COPPER 136 
#define  E1000_DEV_ID_82544EI_FIBER 135 
#define  E1000_DEV_ID_82544GC_COPPER 134 
#define  E1000_DEV_ID_82544GC_LOM 133 
#define  E1000_DEV_ID_82545EM_COPPER 132 
#define  E1000_DEV_ID_82545EM_FIBER 131 
#define  E1000_DEV_ID_82546EB_COPPER 130 
#define  E1000_DEV_ID_82546EB_FIBER 129 
#define  E1000_DEV_ID_82546EB_QUAD_COPPER 128 

__attribute__((used)) static int e1000_is_need_ioport(struct pci_dev *pdev)
{
	switch (pdev->device) {
	case E1000_DEV_ID_82540EM:
	case E1000_DEV_ID_82540EM_LOM:
	case E1000_DEV_ID_82540EP:
	case E1000_DEV_ID_82540EP_LOM:
	case E1000_DEV_ID_82540EP_LP:
	case E1000_DEV_ID_82541EI:
	case E1000_DEV_ID_82541EI_MOBILE:
	case E1000_DEV_ID_82541ER:
	case E1000_DEV_ID_82541ER_LOM:
	case E1000_DEV_ID_82541GI:
	case E1000_DEV_ID_82541GI_LF:
	case E1000_DEV_ID_82541GI_MOBILE:
	case E1000_DEV_ID_82544EI_COPPER:
	case E1000_DEV_ID_82544EI_FIBER:
	case E1000_DEV_ID_82544GC_COPPER:
	case E1000_DEV_ID_82544GC_LOM:
	case E1000_DEV_ID_82545EM_COPPER:
	case E1000_DEV_ID_82545EM_FIBER:
	case E1000_DEV_ID_82546EB_COPPER:
	case E1000_DEV_ID_82546EB_FIBER:
	case E1000_DEV_ID_82546EB_QUAD_COPPER:
		return true;
	default:
		return false;
	}
}