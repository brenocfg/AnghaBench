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
struct input_dev {int dummy; } ;
struct hil_dev {int idx4; int* data; struct input_dev* dev; } ;

/* Variables and functions */
 unsigned int HIL_KBD_SET1_SHIFT ; 
 unsigned int HIL_KBD_SET1_UPBIT ; 
 unsigned int HIL_KBD_SET2_SHIFT ; 
 unsigned int HIL_KBD_SET2_UPBIT ; 
 unsigned int HIL_KBD_SET3_SHIFT ; 
 unsigned int HIL_KBD_SET3_UPBIT ; 
#define  HIL_POL_CHARTYPE_ASCII 135 
#define  HIL_POL_CHARTYPE_BINARY 134 
 int HIL_POL_CHARTYPE_MASK ; 
#define  HIL_POL_CHARTYPE_NONE 133 
#define  HIL_POL_CHARTYPE_RSVD1 132 
#define  HIL_POL_CHARTYPE_RSVD2 131 
#define  HIL_POL_CHARTYPE_SET1 130 
#define  HIL_POL_CHARTYPE_SET2 129 
#define  HIL_POL_CHARTYPE_SET3 128 
 unsigned int* hil_kbd_set1 ; 
 unsigned int* hil_kbd_set3 ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,unsigned int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void hil_dev_handle_kbd_events(struct hil_dev *kbd)
{
	struct input_dev *dev = kbd->dev;
	int idx = kbd->idx4 / 4;
	int i;

	switch (kbd->data[0] & HIL_POL_CHARTYPE_MASK) {
	case HIL_POL_CHARTYPE_NONE:
		return;

	case HIL_POL_CHARTYPE_ASCII:
		for (i = 1; i < idx - 1; i++)
			input_report_key(dev, kbd->data[i] & 0x7f, 1);
		break;

	case HIL_POL_CHARTYPE_RSVD1:
	case HIL_POL_CHARTYPE_RSVD2:
	case HIL_POL_CHARTYPE_BINARY:
		for (i = 1; i < idx - 1; i++)
			input_report_key(dev, kbd->data[i], 1);
		break;

	case HIL_POL_CHARTYPE_SET1:
		for (i = 1; i < idx - 1; i++) {
			unsigned int key = kbd->data[i];
			int up = key & HIL_KBD_SET1_UPBIT;

			key &= (~HIL_KBD_SET1_UPBIT & 0xff);
			key = hil_kbd_set1[key >> HIL_KBD_SET1_SHIFT];
			input_report_key(dev, key, !up);
		}
		break;

	case HIL_POL_CHARTYPE_SET2:
		for (i = 1; i < idx - 1; i++) {
			unsigned int key = kbd->data[i];
			int up = key & HIL_KBD_SET2_UPBIT;

			key &= (~HIL_KBD_SET1_UPBIT & 0xff);
			key = key >> HIL_KBD_SET2_SHIFT;
			input_report_key(dev, key, !up);
		}
		break;

	case HIL_POL_CHARTYPE_SET3:
		for (i = 1; i < idx - 1; i++) {
			unsigned int key = kbd->data[i];
			int up = key & HIL_KBD_SET3_UPBIT;

			key &= (~HIL_KBD_SET1_UPBIT & 0xff);
			key = hil_kbd_set3[key >> HIL_KBD_SET3_SHIFT];
			input_report_key(dev, key, !up);
		}
		break;
	}

	input_sync(dev);
}