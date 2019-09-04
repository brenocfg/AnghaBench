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
typedef  unsigned char u16 ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct input_dev {int dummy; } ;
struct hanwang {unsigned char* data; void* current_tool; unsigned char current_id; TYPE_1__* features; struct usb_device* usbdev; struct input_dev* dev; } ;
typedef  enum hanwang_tablet_type { ____Placeholder_hanwang_tablet_type } hanwang_tablet_type ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int type; int pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 void* BTN_0 ; 
 int /*<<< orphan*/  BTN_1 ; 
 int /*<<< orphan*/  BTN_5 ; 
 void* BTN_STYLUS ; 
 void* BTN_STYLUS2 ; 
 void* BTN_TOOL_FINGER ; 
 void* BTN_TOOL_PEN ; 
 void* BTN_TOOL_RUBBER ; 
 unsigned char ERASER_DEVICE_ID ; 
 int /*<<< orphan*/  EV_MSC ; 
#define  HANWANG_ART_MASTER_HD 130 
#define  HANWANG_ART_MASTER_II 129 
#define  HANWANG_ART_MASTER_III 128 
 int /*<<< orphan*/  MSC_SERIAL ; 
 unsigned char PAD_DEVICE_ID ; 
 void* STYLUS_DEVICE_ID ; 
 unsigned char be16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,void*,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void hanwang_parse_packet(struct hanwang *hanwang)
{
	unsigned char *data = hanwang->data;
	struct input_dev *input_dev = hanwang->dev;
	struct usb_device *dev = hanwang->usbdev;
	enum hanwang_tablet_type type = hanwang->features->type;
	int i;
	u16 p;

	if (type == HANWANG_ART_MASTER_II) {
		hanwang->current_tool = BTN_TOOL_PEN;
		hanwang->current_id = STYLUS_DEVICE_ID;
	}

	switch (data[0]) {
	case 0x02:	/* data packet */
		switch (data[1]) {
		case 0x80:	/* tool prox out */
			if (type != HANWANG_ART_MASTER_II) {
				hanwang->current_id = 0;
				input_report_key(input_dev,
						 hanwang->current_tool, 0);
			}
			break;

		case 0x00:	/* artmaster ii pen leave */
			if (type == HANWANG_ART_MASTER_II) {
				hanwang->current_id = 0;
				input_report_key(input_dev,
						 hanwang->current_tool, 0);
			}
			break;

		case 0xc2:	/* first time tool prox in */
			switch (data[3] & 0xf0) {
			case 0x20:	/* art_master III */
			case 0x30:	/* art_master_HD */
				hanwang->current_id = STYLUS_DEVICE_ID;
				hanwang->current_tool = BTN_TOOL_PEN;
				input_report_key(input_dev, BTN_TOOL_PEN, 1);
				break;
			case 0xa0:	/* art_master III */
			case 0xb0:	/* art_master_HD */
				hanwang->current_id = ERASER_DEVICE_ID;
				hanwang->current_tool = BTN_TOOL_RUBBER;
				input_report_key(input_dev, BTN_TOOL_RUBBER, 1);
				break;
			default:
				hanwang->current_id = 0;
				dev_dbg(&dev->dev,
					"unknown tablet tool %02x\n", data[0]);
				break;
			}
			break;

		default:	/* tool data packet */
			switch (type) {
			case HANWANG_ART_MASTER_III:
				p = (data[6] << 3) |
				    ((data[7] & 0xc0) >> 5) |
				    (data[1] & 0x01);
				break;

			case HANWANG_ART_MASTER_HD:
			case HANWANG_ART_MASTER_II:
				p = (data[7] >> 6) | (data[6] << 2);
				break;

			default:
				p = 0;
				break;
			}

			input_report_abs(input_dev, ABS_X,
					 be16_to_cpup((__be16 *)&data[2]));
			input_report_abs(input_dev, ABS_Y,
					 be16_to_cpup((__be16 *)&data[4]));
			input_report_abs(input_dev, ABS_PRESSURE, p);
			input_report_abs(input_dev, ABS_TILT_X, data[7] & 0x3f);
			input_report_abs(input_dev, ABS_TILT_Y, data[8] & 0x7f);
			input_report_key(input_dev, BTN_STYLUS, data[1] & 0x02);

			if (type != HANWANG_ART_MASTER_II)
				input_report_key(input_dev, BTN_STYLUS2,
						 data[1] & 0x04);
			else
				input_report_key(input_dev, BTN_TOOL_PEN, 1);

			break;
		}

		input_report_abs(input_dev, ABS_MISC, hanwang->current_id);
		input_event(input_dev, EV_MSC, MSC_SERIAL,
				hanwang->features->pid);
		break;

	case 0x0c:
		/* roll wheel */
		hanwang->current_id = PAD_DEVICE_ID;

		switch (type) {
		case HANWANG_ART_MASTER_III:
			input_report_key(input_dev, BTN_TOOL_FINGER,
					 data[1] || data[2] || data[3]);
			input_report_abs(input_dev, ABS_WHEEL, data[1]);
			input_report_key(input_dev, BTN_0, data[2]);
			for (i = 0; i < 8; i++)
				input_report_key(input_dev,
					 BTN_1 + i, data[3] & (1 << i));
			break;

		case HANWANG_ART_MASTER_HD:
			input_report_key(input_dev, BTN_TOOL_FINGER, data[1] ||
					data[2] || data[3] || data[4] ||
					data[5] || data[6]);
			input_report_abs(input_dev, ABS_RX,
					((data[1] & 0x1f) << 8) | data[2]);
			input_report_abs(input_dev, ABS_RY,
					((data[3] & 0x1f) << 8) | data[4]);
			input_report_key(input_dev, BTN_0, data[5] & 0x01);
			for (i = 0; i < 4; i++) {
				input_report_key(input_dev,
					 BTN_1 + i, data[5] & (1 << i));
				input_report_key(input_dev,
					 BTN_5 + i, data[6] & (1 << i));
			}
			break;

		case HANWANG_ART_MASTER_II:
			dev_dbg(&dev->dev, "error packet  %02x\n", data[0]);
			return;
		}

		input_report_abs(input_dev, ABS_MISC, hanwang->current_id);
		input_event(input_dev, EV_MSC, MSC_SERIAL, 0xffffffff);
		break;

	default:
		dev_dbg(&dev->dev, "error packet  %02x\n", data[0]);
		break;
	}

	input_sync(input_dev);
}