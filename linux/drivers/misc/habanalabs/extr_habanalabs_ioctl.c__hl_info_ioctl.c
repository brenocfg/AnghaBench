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
struct hl_info_args {int op; } ;
struct hl_fpriv {struct hl_device* hdev; } ;
struct hl_device {int /*<<< orphan*/  in_reset; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOTTY ; 
#define  HL_INFO_DEVICE_STATUS 134 
#define  HL_INFO_DEVICE_UTILIZATION 133 
#define  HL_INFO_DRAM_USAGE 132 
#define  HL_INFO_HW_EVENTS 131 
#define  HL_INFO_HW_EVENTS_AGGREGATE 130 
#define  HL_INFO_HW_IDLE 129 
#define  HL_INFO_HW_IP_INFO 128 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (struct device*,char*,char*) ; 
 int device_status_info (struct hl_device*,struct hl_info_args*) ; 
 int device_utilization (struct hl_device*,struct hl_info_args*) ; 
 int dram_usage_info (struct hl_fpriv*,struct hl_info_args*) ; 
 scalar_t__ hl_device_disabled_or_in_reset (struct hl_device*) ; 
 int hw_events_info (struct hl_device*,int,struct hl_info_args*) ; 
 int hw_idle (struct hl_device*,struct hl_info_args*) ; 
 int hw_ip_info (struct hl_device*,struct hl_info_args*) ; 

__attribute__((used)) static int _hl_info_ioctl(struct hl_fpriv *hpriv, void *data,
				struct device *dev)
{
	struct hl_info_args *args = data;
	struct hl_device *hdev = hpriv->hdev;
	int rc;

	/*
	 * Information is returned for the following opcodes even if the device
	 * is disabled or in reset.
	 */
	switch (args->op) {
	case HL_INFO_HW_IP_INFO:
		return hw_ip_info(hdev, args);

	case HL_INFO_DEVICE_STATUS:
		return device_status_info(hdev, args);

	default:
		break;
	}

	if (hl_device_disabled_or_in_reset(hdev)) {
		dev_warn_ratelimited(dev,
			"Device is %s. Can't execute INFO IOCTL\n",
			atomic_read(&hdev->in_reset) ? "in_reset" : "disabled");
		return -EBUSY;
	}

	switch (args->op) {
	case HL_INFO_HW_EVENTS:
		rc = hw_events_info(hdev, false, args);
		break;

	case HL_INFO_DRAM_USAGE:
		rc = dram_usage_info(hpriv, args);
		break;

	case HL_INFO_HW_IDLE:
		rc = hw_idle(hdev, args);
		break;

	case HL_INFO_DEVICE_UTILIZATION:
		rc = device_utilization(hdev, args);
		break;

	case HL_INFO_HW_EVENTS_AGGREGATE:
		rc = hw_events_info(hdev, true, args);
		break;

	default:
		dev_err(dev, "Invalid request %d\n", args->op);
		rc = -ENOTTY;
		break;
	}

	return rc;
}