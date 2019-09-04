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
struct input_dev {int dummy; } ;
struct elo {unsigned char* data; size_t idx; int csum; unsigned char expected_packet; int /*<<< orphan*/  response; int /*<<< orphan*/  cmd_done; TYPE_1__* serio; struct input_dev* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int ELO10_ACK_PACKET ; 
 unsigned char ELO10_LEAD_BYTE ; 
 int /*<<< orphan*/  ELO10_PACKET_LEN ; 
 int ELO10_PRESSURE ; 
 int ELO10_TOUCH ; 
 unsigned char ELO10_TOUCH_PACKET ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char,...) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elo_process_data_10(struct elo *elo, unsigned char data)
{
	struct input_dev *dev = elo->dev;

	elo->data[elo->idx] = data;

	switch (elo->idx++) {
	case 0:
		elo->csum = 0xaa;
		if (data != ELO10_LEAD_BYTE) {
			dev_dbg(&elo->serio->dev,
				"unsynchronized data: 0x%02x\n", data);
			elo->idx = 0;
		}
		break;

	case 9:
		elo->idx = 0;
		if (data != elo->csum) {
			dev_dbg(&elo->serio->dev,
				"bad checksum: 0x%02x, expected 0x%02x\n",
				 data, elo->csum);
			break;
		}
		if (elo->data[1] != elo->expected_packet) {
			if (elo->data[1] != ELO10_TOUCH_PACKET)
				dev_dbg(&elo->serio->dev,
					"unexpected packet: 0x%02x\n",
					 elo->data[1]);
			break;
		}
		if (likely(elo->data[1] == ELO10_TOUCH_PACKET)) {
			input_report_abs(dev, ABS_X, (elo->data[4] << 8) | elo->data[3]);
			input_report_abs(dev, ABS_Y, (elo->data[6] << 8) | elo->data[5]);
			if (elo->data[2] & ELO10_PRESSURE)
				input_report_abs(dev, ABS_PRESSURE,
						(elo->data[8] << 8) | elo->data[7]);
			input_report_key(dev, BTN_TOUCH, elo->data[2] & ELO10_TOUCH);
			input_sync(dev);
		} else if (elo->data[1] == ELO10_ACK_PACKET) {
			if (elo->data[2] == '0')
				elo->expected_packet = ELO10_TOUCH_PACKET;
			complete(&elo->cmd_done);
		} else {
			memcpy(elo->response, &elo->data[1], ELO10_PACKET_LEN);
			elo->expected_packet = ELO10_ACK_PACKET;
		}
		break;
	}
	elo->csum += data;
}