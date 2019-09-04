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
typedef  int /*<<< orphan*/  touch_data ;
struct icn8505_touch_data {int touch_count; int softbutton; struct icn8505_touch* touches; } ;
struct icn8505_touch {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  slot; int /*<<< orphan*/  event; } ;
struct icn8505_data {int /*<<< orphan*/  input; int /*<<< orphan*/  prop; TYPE_1__* client; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ICN8505_MAX_TOUCHES ; 
 int /*<<< orphan*/  ICN8505_REG_TOUCHDATA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_LEFTMETA ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ ) ; 
 int icn8505_read_data (struct icn8505_data*,int /*<<< orphan*/ ,struct icn8505_touch_data*,int) ; 
 int icn8505_touch_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_sync_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touchscreen_report_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t icn8505_irq(int irq, void *dev_id)
{
	struct icn8505_data *icn8505 = dev_id;
	struct device *dev = &icn8505->client->dev;
	struct icn8505_touch_data touch_data;
	int i, error;

	error = icn8505_read_data(icn8505, ICN8505_REG_TOUCHDATA,
				  &touch_data, sizeof(touch_data));
	if (error) {
		dev_err(dev, "Error reading touch data: %d\n", error);
		return IRQ_HANDLED;
	}

	if (touch_data.touch_count > ICN8505_MAX_TOUCHES) {
		dev_warn(dev, "Too many touches %d > %d\n",
			 touch_data.touch_count, ICN8505_MAX_TOUCHES);
		touch_data.touch_count = ICN8505_MAX_TOUCHES;
	}

	for (i = 0; i < touch_data.touch_count; i++) {
		struct icn8505_touch *touch = &touch_data.touches[i];
		bool act = icn8505_touch_active(touch->event);

		input_mt_slot(icn8505->input, touch->slot);
		input_mt_report_slot_state(icn8505->input, MT_TOOL_FINGER, act);
		if (!act)
			continue;

		touchscreen_report_pos(icn8505->input, &icn8505->prop,
				       get_unaligned_le16(touch->x),
				       get_unaligned_le16(touch->y),
				       true);
	}

	input_mt_sync_frame(icn8505->input);
	input_report_key(icn8505->input, KEY_LEFTMETA,
			 touch_data.softbutton == 1);
	input_sync(icn8505->input);

	return IRQ_HANDLED;
}