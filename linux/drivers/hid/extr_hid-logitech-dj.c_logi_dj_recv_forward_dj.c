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
struct dj_report {size_t device_index; int report_type; } ;
struct dj_receiver_dev {struct dj_device** paired_dj_devices; } ;
struct dj_device {int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int /*<<< orphan*/  dbg_hid (char*,...) ; 
 scalar_t__ hid_input_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,scalar_t__,int) ; 
 scalar_t__* hid_reportid_size_map ; 

__attribute__((used)) static void logi_dj_recv_forward_dj(struct dj_receiver_dev *djrcv_dev,
				    struct dj_report *dj_report)
{
	/* We are called from atomic context (tasklet && djrcv->lock held) */
	struct dj_device *dj_device;

	dj_device = djrcv_dev->paired_dj_devices[dj_report->device_index];

	if ((dj_report->report_type > ARRAY_SIZE(hid_reportid_size_map) - 1) ||
	    (hid_reportid_size_map[dj_report->report_type] == 0)) {
		dbg_hid("invalid report type:%x\n", dj_report->report_type);
		return;
	}

	if (hid_input_report(dj_device->hdev,
			HID_INPUT_REPORT, &dj_report->report_type,
			hid_reportid_size_map[dj_report->report_type], 1)) {
		dbg_hid("hid_input_report error\n");
	}
}