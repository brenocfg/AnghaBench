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
#define  COMP_COMMAND_ABORTED 135 
#define  COMP_COMMAND_RING_STOPPED 134 
#define  COMP_CONTEXT_STATE_ERROR 133 
#define  COMP_INCOMPATIBLE_DEVICE_ERROR 132 
#define  COMP_MAX_EXIT_LATENCY_TOO_LARGE_ERROR 131 
#define  COMP_PARAMETER_ERROR 130 
#define  COMP_SLOT_NOT_ENABLED_ERROR 129 
#define  COMP_SUCCESS 128 
 int EINVAL ; 
 int ENODEV ; 
 int ETIME ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  trace_xhci_dbg_context_change ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*,int) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*) ; 

__attribute__((used)) static int xhci_evaluate_context_result(struct xhci_hcd *xhci,
		struct usb_device *udev, u32 *cmd_status)
{
	int ret;

	switch (*cmd_status) {
	case COMP_COMMAND_ABORTED:
	case COMP_COMMAND_RING_STOPPED:
		xhci_warn(xhci, "Timeout while waiting for evaluate context command\n");
		ret = -ETIME;
		break;
	case COMP_PARAMETER_ERROR:
		dev_warn(&udev->dev,
			 "WARN: xHCI driver setup invalid evaluate context command.\n");
		ret = -EINVAL;
		break;
	case COMP_SLOT_NOT_ENABLED_ERROR:
		dev_warn(&udev->dev,
			"WARN: slot not enabled for evaluate context command.\n");
		ret = -EINVAL;
		break;
	case COMP_CONTEXT_STATE_ERROR:
		dev_warn(&udev->dev,
			"WARN: invalid context state for evaluate context command.\n");
		ret = -EINVAL;
		break;
	case COMP_INCOMPATIBLE_DEVICE_ERROR:
		dev_warn(&udev->dev,
			"ERROR: Incompatible device for evaluate context command.\n");
		ret = -ENODEV;
		break;
	case COMP_MAX_EXIT_LATENCY_TOO_LARGE_ERROR:
		/* Max Exit Latency too large error */
		dev_warn(&udev->dev, "WARN: Max Exit Latency too large\n");
		ret = -EINVAL;
		break;
	case COMP_SUCCESS:
		xhci_dbg_trace(xhci, trace_xhci_dbg_context_change,
				"Successful evaluate context command");
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