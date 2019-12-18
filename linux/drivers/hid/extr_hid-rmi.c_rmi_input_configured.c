#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct input_dev* input; } ;
struct rmi_data {int device_flags; int /*<<< orphan*/  flags; TYPE_1__ xport; } ;
struct input_dev {int dummy; } ;
struct hid_input {struct input_dev* input; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RMI_DEVICE ; 
 int /*<<< orphan*/  RMI_MODE_ATTN_REPORTS ; 
 int /*<<< orphan*/  RMI_STARTED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*) ; 
 int /*<<< orphan*/  hid_device_io_start (struct hid_device*) ; 
 int /*<<< orphan*/  hid_device_io_stop (struct hid_device*) ; 
 struct rmi_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_close (struct hid_device*) ; 
 int hid_hw_open (struct hid_device*) ; 
 int rmi_register_transport_device (TYPE_1__*) ; 
 int rmi_set_mode (struct hid_device*,int /*<<< orphan*/ ) ; 
 int rmi_set_page (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rmi_input_configured(struct hid_device *hdev, struct hid_input *hi)
{
	struct rmi_data *data = hid_get_drvdata(hdev);
	struct input_dev *input = hi->input;
	int ret = 0;

	if (!(data->device_flags & RMI_DEVICE))
		return 0;

	data->xport.input = input;

	hid_dbg(hdev, "Opening low level driver\n");
	ret = hid_hw_open(hdev);
	if (ret)
		return ret;

	/* Allow incoming hid reports */
	hid_device_io_start(hdev);

	ret = rmi_set_mode(hdev, RMI_MODE_ATTN_REPORTS);
	if (ret < 0) {
		dev_err(&hdev->dev, "failed to set rmi mode\n");
		goto exit;
	}

	ret = rmi_set_page(hdev, 0);
	if (ret < 0) {
		dev_err(&hdev->dev, "failed to set page select to 0.\n");
		goto exit;
	}

	ret = rmi_register_transport_device(&data->xport);
	if (ret < 0) {
		dev_err(&hdev->dev, "failed to register transport driver\n");
		goto exit;
	}

	set_bit(RMI_STARTED, &data->flags);

exit:
	hid_device_io_stop(hdev);
	hid_hw_close(hdev);
	return ret;
}