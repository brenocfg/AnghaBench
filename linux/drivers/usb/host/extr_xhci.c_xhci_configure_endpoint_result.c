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
typedef  int u32 ;
struct xhci_hcd {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  COMP_BANDWIDTH_ERROR 135 
#define  COMP_COMMAND_ABORTED 134 
#define  COMP_COMMAND_RING_STOPPED 133 
#define  COMP_INCOMPATIBLE_DEVICE_ERROR 132 
#define  COMP_RESOURCE_ERROR 131 
#define  COMP_SECONDARY_BANDWIDTH_ERROR 130 
#define  COMP_SUCCESS 129 
#define  COMP_TRB_ERROR 128 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ETIME ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  trace_xhci_dbg_context_change ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*,int) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*) ; 

__attribute__((used)) static int xhci_configure_endpoint_result(struct xhci_hcd *xhci,
		struct usb_device *udev, u32 *cmd_status)
{
	int ret;

	switch (*cmd_status) {
	case COMP_COMMAND_ABORTED:
	case COMP_COMMAND_RING_STOPPED:
		xhci_warn(xhci, "Timeout while waiting for configure endpoint command\n");
		ret = -ETIME;
		break;
	case COMP_RESOURCE_ERROR:
		dev_warn(&udev->dev,
			 "Not enough host controller resources for new device state.\n");
		ret = -ENOMEM;
		/* FIXME: can we allocate more resources for the HC? */
		break;
	case COMP_BANDWIDTH_ERROR:
	case COMP_SECONDARY_BANDWIDTH_ERROR:
		dev_warn(&udev->dev,
			 "Not enough bandwidth for new device state.\n");
		ret = -ENOSPC;
		/* FIXME: can we go back to the old state? */
		break;
	case COMP_TRB_ERROR:
		/* the HCD set up something wrong */
		dev_warn(&udev->dev, "ERROR: Endpoint drop flag = 0, "
				"add flag = 1, "
				"and endpoint is not disabled.\n");
		ret = -EINVAL;
		break;
	case COMP_INCOMPATIBLE_DEVICE_ERROR:
		dev_warn(&udev->dev,
			 "ERROR: Incompatible device for endpoint configure command.\n");
		ret = -ENODEV;
		break;
	case COMP_SUCCESS:
		xhci_dbg_trace(xhci, trace_xhci_dbg_context_change,
				"Successful Endpoint Configure command");
		ret = 0;
		break;
	default:
		xhci_err(xhci, "ERROR: unexpected command completion code 0x%x.\n",
				*cmd_status);
		ret = -EINVAL;
		break;
	}
	return ret;
}