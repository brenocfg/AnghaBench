#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vmpacket_descriptor {int offset8; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  size; } ;
struct synthhid_msg {TYPE_3__ header; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct synthhid_input_report {struct pipe_prt_msg* buffer; TYPE_1__ header; } ;
struct synthhid_device_info {int dummy; } ;
struct pipe_prt_msg {scalar_t__ type; int size; scalar_t__ data; } ;
struct mousevsc_prt_msg {int dummy; } ;
struct mousevsc_dev {TYPE_2__* device; int /*<<< orphan*/ * input_buf; int /*<<< orphan*/  hid_device; int /*<<< orphan*/  init_complete; int /*<<< orphan*/  wait_event; int /*<<< orphan*/  protocol_resp; } ;
struct hv_input_dev_info {int dummy; } ;
struct hv_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 scalar_t__ PIPE_MESSAGE_DATA ; 
#define  SYNTH_HID_INITIAL_DEVICE_INFO 130 
#define  SYNTH_HID_INPUT_REPORT 129 
#define  SYNTH_HID_PROTOCOL_RESPONSE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_input_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int) ; 
 struct mousevsc_dev* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct pipe_prt_msg*,size_t) ; 
 size_t min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousevsc_on_receive_device_info (struct mousevsc_dev*,struct synthhid_device_info*) ; 
 int /*<<< orphan*/  pm_wakeup_hard_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mousevsc_on_receive(struct hv_device *device,
				struct vmpacket_descriptor *packet)
{
	struct pipe_prt_msg *pipe_msg;
	struct synthhid_msg *hid_msg;
	struct mousevsc_dev *input_dev = hv_get_drvdata(device);
	struct synthhid_input_report *input_report;
	size_t len;

	pipe_msg = (struct pipe_prt_msg *)((unsigned long)packet +
						(packet->offset8 << 3));

	if (pipe_msg->type != PIPE_MESSAGE_DATA)
		return;

	hid_msg = (struct synthhid_msg *)pipe_msg->data;

	switch (hid_msg->header.type) {
	case SYNTH_HID_PROTOCOL_RESPONSE:
		/*
		 * While it will be impossible for us to protect against
		 * malicious/buggy hypervisor/host, add a check here to
		 * ensure we don't corrupt memory.
		 */
		if ((pipe_msg->size + sizeof(struct pipe_prt_msg)
			- sizeof(unsigned char))
			> sizeof(struct mousevsc_prt_msg)) {
			WARN_ON(1);
			break;
		}

		memcpy(&input_dev->protocol_resp, pipe_msg,
		       pipe_msg->size + sizeof(struct pipe_prt_msg) -
		       sizeof(unsigned char));
		complete(&input_dev->wait_event);
		break;

	case SYNTH_HID_INITIAL_DEVICE_INFO:
		WARN_ON(pipe_msg->size < sizeof(struct hv_input_dev_info));

		/*
		 * Parse out the device info into device attr,
		 * hid desc and report desc
		 */
		mousevsc_on_receive_device_info(input_dev,
			(struct synthhid_device_info *)pipe_msg->data);
		break;
	case SYNTH_HID_INPUT_REPORT:
		input_report =
			(struct synthhid_input_report *)pipe_msg->data;
		if (!input_dev->init_complete)
			break;

		len = min(input_report->header.size,
			  (u32)sizeof(input_dev->input_buf));
		memcpy(input_dev->input_buf, input_report->buffer, len);
		hid_input_report(input_dev->hid_device, HID_INPUT_REPORT,
				 input_dev->input_buf, len, 1);

		pm_wakeup_hard_event(&input_dev->device->device);

		break;
	default:
		pr_err("unsupported hid msg type - type %d len %d\n",
		       hid_msg->header.type, hid_msg->header.size);
		break;
	}

}