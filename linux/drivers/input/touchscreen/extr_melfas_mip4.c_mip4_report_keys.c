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
typedef  int u8 ;
struct mip4_ts {int event_format; int key_num; unsigned short* key_code; TYPE_1__* client; int /*<<< orphan*/  input; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,unsigned short,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,unsigned short,int) ; 

__attribute__((used)) static void mip4_report_keys(struct mip4_ts *ts, u8 *packet)
{
	u8 key;
	bool down;

	switch (ts->event_format) {
	case 0:
	case 1:
		key = packet[0] & 0x0F;
		down = packet[0] & 0x80;
		break;

	case 3:
	default:
		key = packet[0] & 0x0F;
		down = packet[1] & 0x01;
		break;
	}

	/* Report key event */
	if (key >= 1 && key <= ts->key_num) {
		unsigned short keycode = ts->key_code[key - 1];

		dev_dbg(&ts->client->dev,
			"Key - ID: %d, keycode: %d, state: %d\n",
			key, keycode, down);

		input_event(ts->input, EV_MSC, MSC_SCAN, keycode);
		input_report_key(ts->input, keycode, down);

	} else {
		dev_err(&ts->client->dev, "Unknown key: %d\n", key);
	}
}