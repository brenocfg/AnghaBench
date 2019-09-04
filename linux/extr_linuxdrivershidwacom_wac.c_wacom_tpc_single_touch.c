#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int touch_max; } ;
struct wacom_wac {unsigned char* data; TYPE_2__* shared; TYPE_1__ features; struct input_dev* touch_input; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int touch_down; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 size_t WACOM_PKGLEN_TPC1FG ; 
 size_t WACOM_PKGLEN_TPC1FG_B ; 
 size_t WACOM_PKGLEN_TPC2FG ; 
 int get_unaligned_le16 (unsigned char*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 
 int report_touch_events (struct wacom_wac*) ; 

__attribute__((used)) static int wacom_tpc_single_touch(struct wacom_wac *wacom, size_t len)
{
	unsigned char *data = wacom->data;
	struct input_dev *input = wacom->touch_input;
	bool prox = report_touch_events(wacom);
	int x = 0, y = 0;

	if (wacom->features.touch_max > 1 || len > WACOM_PKGLEN_TPC2FG)
		return 0;

	if (len == WACOM_PKGLEN_TPC1FG) {
		prox = prox && (data[0] & 0x01);
		x = get_unaligned_le16(&data[1]);
		y = get_unaligned_le16(&data[3]);
	} else if (len == WACOM_PKGLEN_TPC1FG_B) {
		prox = prox && (data[2] & 0x01);
		x = get_unaligned_le16(&data[3]);
		y = get_unaligned_le16(&data[5]);
	} else {
		prox = prox && (data[1] & 0x01);
		x = le16_to_cpup((__le16 *)&data[2]);
		y = le16_to_cpup((__le16 *)&data[4]);
	}

	if (prox) {
		input_report_abs(input, ABS_X, x);
		input_report_abs(input, ABS_Y, y);
	}
	input_report_key(input, BTN_TOUCH, prox);

	/* keep touch state for pen events */
	wacom->shared->touch_down = prox;

	return 1;
}