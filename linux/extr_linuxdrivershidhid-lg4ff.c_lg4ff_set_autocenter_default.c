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
typedef  int u32 ;
typedef  int u16 ;
struct lg_drv_data {struct lg4ff_device_entry* device_props; } ;
struct TYPE_5__ {int product_id; } ;
struct lg4ff_device_entry {int /*<<< orphan*/  report_lock; TYPE_3__* report; TYPE_2__ wdata; } ;
struct input_dev {int dummy; } ;
struct hid_device {int dummy; } ;
typedef  int s32 ;
struct TYPE_6__ {TYPE_1__** field; } ;
struct TYPE_4__ {int* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
#define  USB_DEVICE_ID_LOGITECH_MOMO_WHEEL 129 
#define  USB_DEVICE_ID_LOGITECH_MOMO_WHEEL2 128 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 struct lg_drv_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_request (struct hid_device*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct hid_device* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void lg4ff_set_autocenter_default(struct input_dev *dev, u16 magnitude)
{
	struct hid_device *hid = input_get_drvdata(dev);
	s32 *value;
	u32 expand_a, expand_b;
	struct lg4ff_device_entry *entry;
	struct lg_drv_data *drv_data;
	unsigned long flags;

	drv_data = hid_get_drvdata(hid);
	if (!drv_data) {
		hid_err(hid, "Private driver data not found!\n");
		return;
	}

	entry = drv_data->device_props;
	if (!entry) {
		hid_err(hid, "Device properties not found!\n");
		return;
	}
	value = entry->report->field[0]->value;

	/* De-activate Auto-Center */
	spin_lock_irqsave(&entry->report_lock, flags);
	if (magnitude == 0) {
		value[0] = 0xf5;
		value[1] = 0x00;
		value[2] = 0x00;
		value[3] = 0x00;
		value[4] = 0x00;
		value[5] = 0x00;
		value[6] = 0x00;

		hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
		spin_unlock_irqrestore(&entry->report_lock, flags);
		return;
	}

	if (magnitude <= 0xaaaa) {
		expand_a = 0x0c * magnitude;
		expand_b = 0x80 * magnitude;
	} else {
		expand_a = (0x0c * 0xaaaa) + 0x06 * (magnitude - 0xaaaa);
		expand_b = (0x80 * 0xaaaa) + 0xff * (magnitude - 0xaaaa);
	}

	/* Adjust for non-MOMO wheels */
	switch (entry->wdata.product_id) {
	case USB_DEVICE_ID_LOGITECH_MOMO_WHEEL:
	case USB_DEVICE_ID_LOGITECH_MOMO_WHEEL2:
		break;
	default:
		expand_a = expand_a >> 1;
		break;
	}

	value[0] = 0xfe;
	value[1] = 0x0d;
	value[2] = expand_a / 0xaaaa;
	value[3] = expand_a / 0xaaaa;
	value[4] = expand_b / 0xaaaa;
	value[5] = 0x00;
	value[6] = 0x00;

	hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);

	/* Activate Auto-Center */
	value[0] = 0x14;
	value[1] = 0x00;
	value[2] = 0x00;
	value[3] = 0x00;
	value[4] = 0x00;
	value[5] = 0x00;
	value[6] = 0x00;

	hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&entry->report_lock, flags);
}