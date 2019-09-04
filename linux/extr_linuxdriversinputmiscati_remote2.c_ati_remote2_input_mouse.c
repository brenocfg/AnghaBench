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
struct input_dev {int dummy; } ;
struct ati_remote2 {int** buf; int channel_mask; int mode_mask; TYPE_1__** intf; struct input_dev* idev; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATI_REMOTE2_PC ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,int,int) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void ati_remote2_input_mouse(struct ati_remote2 *ar2)
{
	struct input_dev *idev = ar2->idev;
	u8 *data = ar2->buf[0];
	int channel, mode;

	channel = data[0] >> 4;

	if (!((1 << channel) & ar2->channel_mask))
		return;

	mode = data[0] & 0x0F;

	if (mode > ATI_REMOTE2_PC) {
		dev_err(&ar2->intf[0]->dev,
			"Unknown mode byte (%02x %02x %02x %02x)\n",
			data[3], data[2], data[1], data[0]);
		return;
	}

	if (!((1 << mode) & ar2->mode_mask))
		return;

	input_event(idev, EV_REL, REL_X, (s8) data[1]);
	input_event(idev, EV_REL, REL_Y, (s8) data[2]);
	input_sync(idev);
}