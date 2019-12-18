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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  otg_cap; } ;
struct TYPE_3__ {int op_mode; } ;
struct dwc2_hsotg {TYPE_2__ params; TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_CAP_PARAM_HNP_SRP_CAPABLE ; 
 int /*<<< orphan*/  DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE ; 
#define  GHWCFG2_OP_MODE_HNP_SRP_CAPABLE 134 
#define  GHWCFG2_OP_MODE_NO_HNP_SRP_CAPABLE 133 
#define  GHWCFG2_OP_MODE_NO_SRP_CAPABLE_DEVICE 132 
#define  GHWCFG2_OP_MODE_NO_SRP_CAPABLE_HOST 131 
#define  GHWCFG2_OP_MODE_SRP_CAPABLE_DEVICE 130 
#define  GHWCFG2_OP_MODE_SRP_CAPABLE_HOST 129 
#define  GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE 128 
 int /*<<< orphan*/  GUSBCFG ; 
 int GUSBCFG_HNPCAP ; 
 int GUSBCFG_SRPCAP ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_gusbcfg_init(struct dwc2_hsotg *hsotg)
{
	u32 usbcfg;

	usbcfg = dwc2_readl(hsotg, GUSBCFG);
	usbcfg &= ~(GUSBCFG_HNPCAP | GUSBCFG_SRPCAP);

	switch (hsotg->hw_params.op_mode) {
	case GHWCFG2_OP_MODE_HNP_SRP_CAPABLE:
		if (hsotg->params.otg_cap ==
				DWC2_CAP_PARAM_HNP_SRP_CAPABLE)
			usbcfg |= GUSBCFG_HNPCAP;
		if (hsotg->params.otg_cap !=
				DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE)
			usbcfg |= GUSBCFG_SRPCAP;
		break;

	case GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE:
	case GHWCFG2_OP_MODE_SRP_CAPABLE_DEVICE:
	case GHWCFG2_OP_MODE_SRP_CAPABLE_HOST:
		if (hsotg->params.otg_cap !=
				DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE)
			usbcfg |= GUSBCFG_SRPCAP;
		break;

	case GHWCFG2_OP_MODE_NO_HNP_SRP_CAPABLE:
	case GHWCFG2_OP_MODE_NO_SRP_CAPABLE_DEVICE:
	case GHWCFG2_OP_MODE_NO_SRP_CAPABLE_HOST:
	default:
		break;
	}

	dwc2_writel(hsotg, usbcfg, GUSBCFG);
}