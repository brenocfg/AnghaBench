#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_6__ {int* DeviceRemovable; } ;
struct TYPE_7__ {TYPE_1__ hs; } ;
struct usb_hub_descriptor {int bDescLength; int bNbrPorts; int bPwrOn2PwrGood; TYPE_2__ u; int /*<<< orphan*/  bHubContrCurrent; int /*<<< orphan*/  wHubCharacteristics; int /*<<< orphan*/  bDescriptorType; } ;
struct TYPE_8__ {int dma_desc_enable; int power_down; int /*<<< orphan*/  dma_desc_fs_enable; } ;
struct TYPE_9__ {int /*<<< orphan*/  port_connect_status; int /*<<< orphan*/  port_over_current_change; int /*<<< orphan*/  port_reset_change; int /*<<< orphan*/  port_l1_change; int /*<<< orphan*/  port_suspend_change; int /*<<< orphan*/  port_enable_change; int /*<<< orphan*/  port_connect_status_change; } ;
struct TYPE_10__ {TYPE_4__ b; int /*<<< orphan*/  d32; } ;
struct dwc2_hsotg {int new_connection; int otg_port; int /*<<< orphan*/  dev; int /*<<< orphan*/  lx_state; int /*<<< orphan*/  hibernated; TYPE_3__ params; TYPE_5__ flags; int /*<<< orphan*/  bus_suspended; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
#define  C_HUB_LOCAL_POWER 148 
#define  C_HUB_OVER_CURRENT 147 
#define  ClearHubFeature 146 
#define  ClearPortFeature 145 
 int /*<<< orphan*/  DWC2_L0 ; 
 int EINVAL ; 
#define  GetHubDescriptor 144 
#define  GetHubStatus 143 
#define  GetPortStatus 142 
 int /*<<< orphan*/  HCFG ; 
 int HCFG_DESCDMA ; 
 int /*<<< orphan*/  HPRT0 ; 
 int HPRT0_CONNSTS ; 
 int HPRT0_ENA ; 
 int HPRT0_OVRCURRACT ; 
 int HPRT0_PWR ; 
 int HPRT0_RST ; 
 int HPRT0_SPD_HIGH_SPEED ; 
 int HPRT0_SPD_LOW_SPEED ; 
 int HPRT0_SPD_MASK ; 
 int HPRT0_SPD_SHIFT ; 
 int HPRT0_SUSP ; 
 int HPRT0_TSTCTL_MASK ; 
 int HPRT0_TSTCTL_SHIFT ; 
 int HUB_CHAR_COMMON_LPSM ; 
 int HUB_CHAR_INDV_PORT_OCPM ; 
 int /*<<< orphan*/  PCGCTL ; 
 int PCGCTL_ENBL_SLEEP_GATING ; 
 int PCGCTL_STOPPCLK ; 
#define  SetHubFeature 141 
#define  SetPortFeature 140 
 int /*<<< orphan*/  USB_DT_HUB ; 
#define  USB_PORT_FEAT_C_CONNECTION 139 
#define  USB_PORT_FEAT_C_ENABLE 138 
#define  USB_PORT_FEAT_C_OVER_CURRENT 137 
#define  USB_PORT_FEAT_C_PORT_L1 136 
#define  USB_PORT_FEAT_C_RESET 135 
#define  USB_PORT_FEAT_C_SUSPEND 134 
#define  USB_PORT_FEAT_ENABLE 133 
#define  USB_PORT_FEAT_INDICATOR 132 
 int USB_PORT_FEAT_L1 ; 
#define  USB_PORT_FEAT_POWER 131 
#define  USB_PORT_FEAT_RESET 130 
#define  USB_PORT_FEAT_SUSPEND 129 
#define  USB_PORT_FEAT_TEST 128 
 int USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_C_CONNECTION ; 
 int USB_PORT_STAT_C_ENABLE ; 
 int USB_PORT_STAT_C_L1 ; 
 int USB_PORT_STAT_C_OVERCURRENT ; 
 int USB_PORT_STAT_C_RESET ; 
 int USB_PORT_STAT_C_SUSPEND ; 
 int USB_PORT_STAT_ENABLE ; 
 int USB_PORT_STAT_HIGH_SPEED ; 
 int USB_PORT_STAT_LOW_SPEED ; 
 int USB_PORT_STAT_OVERCURRENT ; 
 int USB_PORT_STAT_POWER ; 
 int USB_PORT_STAT_RESET ; 
 int USB_PORT_STAT_SUSPEND ; 
 int USB_PORT_STAT_TEST ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc2_enter_hibernation (struct dwc2_hsotg*,int) ; 
 int /*<<< orphan*/  dwc2_exit_hibernation (struct dwc2_hsotg*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dwc2_hcd_is_b_host (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_port_resume (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_port_suspend (struct dwc2_hsotg*,int) ; 
 int dwc2_read_hprt0 (struct dwc2_hsotg*) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_vbus_supply_exit (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_vbus_supply_init (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dwc2_hcd_hub_control(struct dwc2_hsotg *hsotg, u16 typereq,
				u16 wvalue, u16 windex, char *buf, u16 wlength)
{
	struct usb_hub_descriptor *hub_desc;
	int retval = 0;
	u32 hprt0;
	u32 port_status;
	u32 speed;
	u32 pcgctl;
	u32 pwr;

	switch (typereq) {
	case ClearHubFeature:
		dev_dbg(hsotg->dev, "ClearHubFeature %1xh\n", wvalue);

		switch (wvalue) {
		case C_HUB_LOCAL_POWER:
		case C_HUB_OVER_CURRENT:
			/* Nothing required here */
			break;

		default:
			retval = -EINVAL;
			dev_err(hsotg->dev,
				"ClearHubFeature request %1xh unknown\n",
				wvalue);
		}
		break;

	case ClearPortFeature:
		if (wvalue != USB_PORT_FEAT_L1)
			if (!windex || windex > 1)
				goto error;
		switch (wvalue) {
		case USB_PORT_FEAT_ENABLE:
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_ENABLE\n");
			hprt0 = dwc2_read_hprt0(hsotg);
			hprt0 |= HPRT0_ENA;
			dwc2_writel(hsotg, hprt0, HPRT0);
			break;

		case USB_PORT_FEAT_SUSPEND:
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_SUSPEND\n");

			if (hsotg->bus_suspended) {
				if (hsotg->hibernated)
					dwc2_exit_hibernation(hsotg, 0, 0, 1);
				else
					dwc2_port_resume(hsotg);
			}
			break;

		case USB_PORT_FEAT_POWER:
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_POWER\n");
			hprt0 = dwc2_read_hprt0(hsotg);
			pwr = hprt0 & HPRT0_PWR;
			hprt0 &= ~HPRT0_PWR;
			dwc2_writel(hsotg, hprt0, HPRT0);
			if (pwr)
				dwc2_vbus_supply_exit(hsotg);
			break;

		case USB_PORT_FEAT_INDICATOR:
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_INDICATOR\n");
			/* Port indicator not supported */
			break;

		case USB_PORT_FEAT_C_CONNECTION:
			/*
			 * Clears driver's internal Connect Status Change flag
			 */
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_C_CONNECTION\n");
			hsotg->flags.b.port_connect_status_change = 0;
			break;

		case USB_PORT_FEAT_C_RESET:
			/* Clears driver's internal Port Reset Change flag */
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_C_RESET\n");
			hsotg->flags.b.port_reset_change = 0;
			break;

		case USB_PORT_FEAT_C_ENABLE:
			/*
			 * Clears the driver's internal Port Enable/Disable
			 * Change flag
			 */
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_C_ENABLE\n");
			hsotg->flags.b.port_enable_change = 0;
			break;

		case USB_PORT_FEAT_C_SUSPEND:
			/*
			 * Clears the driver's internal Port Suspend Change
			 * flag, which is set when resume signaling on the host
			 * port is complete
			 */
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_C_SUSPEND\n");
			hsotg->flags.b.port_suspend_change = 0;
			break;

		case USB_PORT_FEAT_C_PORT_L1:
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_C_PORT_L1\n");
			hsotg->flags.b.port_l1_change = 0;
			break;

		case USB_PORT_FEAT_C_OVER_CURRENT:
			dev_dbg(hsotg->dev,
				"ClearPortFeature USB_PORT_FEAT_C_OVER_CURRENT\n");
			hsotg->flags.b.port_over_current_change = 0;
			break;

		default:
			retval = -EINVAL;
			dev_err(hsotg->dev,
				"ClearPortFeature request %1xh unknown or unsupported\n",
				wvalue);
		}
		break;

	case GetHubDescriptor:
		dev_dbg(hsotg->dev, "GetHubDescriptor\n");
		hub_desc = (struct usb_hub_descriptor *)buf;
		hub_desc->bDescLength = 9;
		hub_desc->bDescriptorType = USB_DT_HUB;
		hub_desc->bNbrPorts = 1;
		hub_desc->wHubCharacteristics =
			cpu_to_le16(HUB_CHAR_COMMON_LPSM |
				    HUB_CHAR_INDV_PORT_OCPM);
		hub_desc->bPwrOn2PwrGood = 1;
		hub_desc->bHubContrCurrent = 0;
		hub_desc->u.hs.DeviceRemovable[0] = 0;
		hub_desc->u.hs.DeviceRemovable[1] = 0xff;
		break;

	case GetHubStatus:
		dev_dbg(hsotg->dev, "GetHubStatus\n");
		memset(buf, 0, 4);
		break;

	case GetPortStatus:
		dev_vdbg(hsotg->dev,
			 "GetPortStatus wIndex=0x%04x flags=0x%08x\n", windex,
			 hsotg->flags.d32);
		if (!windex || windex > 1)
			goto error;

		port_status = 0;
		if (hsotg->flags.b.port_connect_status_change)
			port_status |= USB_PORT_STAT_C_CONNECTION << 16;
		if (hsotg->flags.b.port_enable_change)
			port_status |= USB_PORT_STAT_C_ENABLE << 16;
		if (hsotg->flags.b.port_suspend_change)
			port_status |= USB_PORT_STAT_C_SUSPEND << 16;
		if (hsotg->flags.b.port_l1_change)
			port_status |= USB_PORT_STAT_C_L1 << 16;
		if (hsotg->flags.b.port_reset_change)
			port_status |= USB_PORT_STAT_C_RESET << 16;
		if (hsotg->flags.b.port_over_current_change) {
			dev_warn(hsotg->dev, "Overcurrent change detected\n");
			port_status |= USB_PORT_STAT_C_OVERCURRENT << 16;
		}

		if (!hsotg->flags.b.port_connect_status) {
			/*
			 * The port is disconnected, which means the core is
			 * either in device mode or it soon will be. Just
			 * return 0's for the remainder of the port status
			 * since the port register can't be read if the core
			 * is in device mode.
			 */
			*(__le32 *)buf = cpu_to_le32(port_status);
			break;
		}

		hprt0 = dwc2_readl(hsotg, HPRT0);
		dev_vdbg(hsotg->dev, "  HPRT0: 0x%08x\n", hprt0);

		if (hprt0 & HPRT0_CONNSTS)
			port_status |= USB_PORT_STAT_CONNECTION;
		if (hprt0 & HPRT0_ENA)
			port_status |= USB_PORT_STAT_ENABLE;
		if (hprt0 & HPRT0_SUSP)
			port_status |= USB_PORT_STAT_SUSPEND;
		if (hprt0 & HPRT0_OVRCURRACT)
			port_status |= USB_PORT_STAT_OVERCURRENT;
		if (hprt0 & HPRT0_RST)
			port_status |= USB_PORT_STAT_RESET;
		if (hprt0 & HPRT0_PWR)
			port_status |= USB_PORT_STAT_POWER;

		speed = (hprt0 & HPRT0_SPD_MASK) >> HPRT0_SPD_SHIFT;
		if (speed == HPRT0_SPD_HIGH_SPEED)
			port_status |= USB_PORT_STAT_HIGH_SPEED;
		else if (speed == HPRT0_SPD_LOW_SPEED)
			port_status |= USB_PORT_STAT_LOW_SPEED;

		if (hprt0 & HPRT0_TSTCTL_MASK)
			port_status |= USB_PORT_STAT_TEST;
		/* USB_PORT_FEAT_INDICATOR unsupported always 0 */

		if (hsotg->params.dma_desc_fs_enable) {
			/*
			 * Enable descriptor DMA only if a full speed
			 * device is connected.
			 */
			if (hsotg->new_connection &&
			    ((port_status &
			      (USB_PORT_STAT_CONNECTION |
			       USB_PORT_STAT_HIGH_SPEED |
			       USB_PORT_STAT_LOW_SPEED)) ==
			       USB_PORT_STAT_CONNECTION)) {
				u32 hcfg;

				dev_info(hsotg->dev, "Enabling descriptor DMA mode\n");
				hsotg->params.dma_desc_enable = true;
				hcfg = dwc2_readl(hsotg, HCFG);
				hcfg |= HCFG_DESCDMA;
				dwc2_writel(hsotg, hcfg, HCFG);
				hsotg->new_connection = false;
			}
		}

		dev_vdbg(hsotg->dev, "port_status=%08x\n", port_status);
		*(__le32 *)buf = cpu_to_le32(port_status);
		break;

	case SetHubFeature:
		dev_dbg(hsotg->dev, "SetHubFeature\n");
		/* No HUB features supported */
		break;

	case SetPortFeature:
		dev_dbg(hsotg->dev, "SetPortFeature\n");
		if (wvalue != USB_PORT_FEAT_TEST && (!windex || windex > 1))
			goto error;

		if (!hsotg->flags.b.port_connect_status) {
			/*
			 * The port is disconnected, which means the core is
			 * either in device mode or it soon will be. Just
			 * return without doing anything since the port
			 * register can't be written if the core is in device
			 * mode.
			 */
			break;
		}

		switch (wvalue) {
		case USB_PORT_FEAT_SUSPEND:
			dev_dbg(hsotg->dev,
				"SetPortFeature - USB_PORT_FEAT_SUSPEND\n");
			if (windex != hsotg->otg_port)
				goto error;
			if (hsotg->params.power_down == 2)
				dwc2_enter_hibernation(hsotg, 1);
			else
				dwc2_port_suspend(hsotg, windex);
			break;

		case USB_PORT_FEAT_POWER:
			dev_dbg(hsotg->dev,
				"SetPortFeature - USB_PORT_FEAT_POWER\n");
			hprt0 = dwc2_read_hprt0(hsotg);
			pwr = hprt0 & HPRT0_PWR;
			hprt0 |= HPRT0_PWR;
			dwc2_writel(hsotg, hprt0, HPRT0);
			if (!pwr)
				dwc2_vbus_supply_init(hsotg);
			break;

		case USB_PORT_FEAT_RESET:
			if (hsotg->params.power_down == 2 &&
			    hsotg->hibernated)
				dwc2_exit_hibernation(hsotg, 0, 1, 1);
			hprt0 = dwc2_read_hprt0(hsotg);
			dev_dbg(hsotg->dev,
				"SetPortFeature - USB_PORT_FEAT_RESET\n");
			pcgctl = dwc2_readl(hsotg, PCGCTL);
			pcgctl &= ~(PCGCTL_ENBL_SLEEP_GATING | PCGCTL_STOPPCLK);
			dwc2_writel(hsotg, pcgctl, PCGCTL);
			/* ??? Original driver does this */
			dwc2_writel(hsotg, 0, PCGCTL);

			hprt0 = dwc2_read_hprt0(hsotg);
			pwr = hprt0 & HPRT0_PWR;
			/* Clear suspend bit if resetting from suspend state */
			hprt0 &= ~HPRT0_SUSP;

			/*
			 * When B-Host the Port reset bit is set in the Start
			 * HCD Callback function, so that the reset is started
			 * within 1ms of the HNP success interrupt
			 */
			if (!dwc2_hcd_is_b_host(hsotg)) {
				hprt0 |= HPRT0_PWR | HPRT0_RST;
				dev_dbg(hsotg->dev,
					"In host mode, hprt0=%08x\n", hprt0);
				dwc2_writel(hsotg, hprt0, HPRT0);
				if (!pwr)
					dwc2_vbus_supply_init(hsotg);
			}

			/* Clear reset bit in 10ms (FS/LS) or 50ms (HS) */
			msleep(50);
			hprt0 &= ~HPRT0_RST;
			dwc2_writel(hsotg, hprt0, HPRT0);
			hsotg->lx_state = DWC2_L0; /* Now back to On state */
			break;

		case USB_PORT_FEAT_INDICATOR:
			dev_dbg(hsotg->dev,
				"SetPortFeature - USB_PORT_FEAT_INDICATOR\n");
			/* Not supported */
			break;

		case USB_PORT_FEAT_TEST:
			hprt0 = dwc2_read_hprt0(hsotg);
			dev_dbg(hsotg->dev,
				"SetPortFeature - USB_PORT_FEAT_TEST\n");
			hprt0 &= ~HPRT0_TSTCTL_MASK;
			hprt0 |= (windex >> 8) << HPRT0_TSTCTL_SHIFT;
			dwc2_writel(hsotg, hprt0, HPRT0);
			break;

		default:
			retval = -EINVAL;
			dev_err(hsotg->dev,
				"SetPortFeature %1xh unknown or unsupported\n",
				wvalue);
			break;
		}
		break;

	default:
error:
		retval = -EINVAL;
		dev_dbg(hsotg->dev,
			"Unknown hub control request: %1xh wIndex: %1xh wValue: %1xh\n",
			typereq, windex, wvalue);
		break;
	}

	return retval;
}