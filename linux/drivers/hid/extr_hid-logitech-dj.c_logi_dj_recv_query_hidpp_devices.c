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
typedef  int u8 ;
typedef  int /*<<< orphan*/  template ;
struct dj_receiver_dev {int /*<<< orphan*/  hidpp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HIDPP_FAKE_DEVICE_ARRIVAL 132 
#define  HIDPP_RECEIVER_INDEX 131 
#define  HIDPP_REG_CONNECTION_STATE 130 
#define  HIDPP_SET_REGISTER 129 
 int /*<<< orphan*/  HID_OUTPUT_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
#define  REPORT_ID_HIDPP_SHORT 128 
 int hid_hw_raw_request (int /*<<< orphan*/ ,int const,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmemdup (int const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int logi_dj_recv_query_hidpp_devices(struct dj_receiver_dev *djrcv_dev)
{
	static const u8 template[] = {
		REPORT_ID_HIDPP_SHORT,
		HIDPP_RECEIVER_INDEX,
		HIDPP_SET_REGISTER,
		HIDPP_REG_CONNECTION_STATE,
		HIDPP_FAKE_DEVICE_ARRIVAL,
		0x00, 0x00
	};
	u8 *hidpp_report;
	int retval;

	hidpp_report = kmemdup(template, sizeof(template), GFP_KERNEL);
	if (!hidpp_report)
		return -ENOMEM;

	retval = hid_hw_raw_request(djrcv_dev->hidpp,
				    REPORT_ID_HIDPP_SHORT,
				    hidpp_report, sizeof(template),
				    HID_OUTPUT_REPORT,
				    HID_REQ_SET_REPORT);

	kfree(hidpp_report);
	return (retval < 0) ? retval : 0;
}