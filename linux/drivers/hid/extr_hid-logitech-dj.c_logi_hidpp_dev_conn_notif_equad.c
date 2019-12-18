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
struct hidpp_event {int* params; } ;
struct hid_device {int dummy; } ;
struct dj_workitem {int device_type; int quad_id_msb; int quad_id_lsb; int reports_supported; int /*<<< orphan*/  type; } ;
struct dj_receiver_dev {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int HIDPP ; 
 int HIDPP_DEVICE_TYPE_MASK ; 
 size_t HIDPP_PARAM_DEVICE_INFO ; 
 size_t HIDPP_PARAM_EQUAD_LSB ; 
 size_t HIDPP_PARAM_EQUAD_MSB ; 
 int MEDIA_CENTER ; 
 int MULTIMEDIA ; 
 int POWER_KEYS ; 
#define  REPORT_TYPE_KEYBOARD 129 
#define  REPORT_TYPE_MOUSE 128 
 int STD_KEYBOARD ; 
 int STD_MOUSE ; 
 int /*<<< orphan*/  WORKITEM_TYPE_PAIRED ; 
 struct dj_receiver_dev* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  recvr_type_mouse_only ; 

__attribute__((used)) static void logi_hidpp_dev_conn_notif_equad(struct hid_device *hdev,
					    struct hidpp_event *hidpp_report,
					    struct dj_workitem *workitem)
{
	struct dj_receiver_dev *djrcv_dev = hid_get_drvdata(hdev);

	workitem->type = WORKITEM_TYPE_PAIRED;
	workitem->device_type = hidpp_report->params[HIDPP_PARAM_DEVICE_INFO] &
				HIDPP_DEVICE_TYPE_MASK;
	workitem->quad_id_msb = hidpp_report->params[HIDPP_PARAM_EQUAD_MSB];
	workitem->quad_id_lsb = hidpp_report->params[HIDPP_PARAM_EQUAD_LSB];
	switch (workitem->device_type) {
	case REPORT_TYPE_KEYBOARD:
		workitem->reports_supported |= STD_KEYBOARD | MULTIMEDIA |
					       POWER_KEYS | MEDIA_CENTER |
					       HIDPP;
		break;
	case REPORT_TYPE_MOUSE:
		workitem->reports_supported |= STD_MOUSE | HIDPP;
		if (djrcv_dev->type == recvr_type_mouse_only)
			workitem->reports_supported |= MULTIMEDIA;
		break;
	}
}