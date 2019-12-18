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
struct stinger {unsigned char* data; int /*<<< orphan*/  idx; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_A ; 
 int /*<<< orphan*/  BTN_B ; 
 int /*<<< orphan*/  BTN_C ; 
 int /*<<< orphan*/  BTN_SELECT ; 
 int /*<<< orphan*/  BTN_START ; 
 int /*<<< orphan*/  BTN_TL ; 
 int /*<<< orphan*/  BTN_TR ; 
 int /*<<< orphan*/  BTN_X ; 
 int /*<<< orphan*/  BTN_Y ; 
 int /*<<< orphan*/  BTN_Z ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void stinger_process_packet(struct stinger *stinger)
{
	struct input_dev *dev = stinger->dev;
	unsigned char *data = stinger->data;

	if (!stinger->idx) return;

	input_report_key(dev, BTN_A,	  ((data[0] & 0x20) >> 5));
	input_report_key(dev, BTN_B,	  ((data[0] & 0x10) >> 4));
	input_report_key(dev, BTN_C,	  ((data[0] & 0x08) >> 3));
	input_report_key(dev, BTN_X,	  ((data[0] & 0x04) >> 2));
	input_report_key(dev, BTN_Y,	  ((data[3] & 0x20) >> 5));
	input_report_key(dev, BTN_Z,	  ((data[3] & 0x10) >> 4));
	input_report_key(dev, BTN_TL,     ((data[3] & 0x08) >> 3));
	input_report_key(dev, BTN_TR,     ((data[3] & 0x04) >> 2));
	input_report_key(dev, BTN_SELECT, ((data[3] & 0x02) >> 1));
	input_report_key(dev, BTN_START,   (data[3] & 0x01));

	input_report_abs(dev, ABS_X, (data[1] & 0x3F) - ((data[0] & 0x01) << 6));
	input_report_abs(dev, ABS_Y, ((data[0] & 0x02) << 5) - (data[2] & 0x3F));

	input_sync(dev);

	return;
}