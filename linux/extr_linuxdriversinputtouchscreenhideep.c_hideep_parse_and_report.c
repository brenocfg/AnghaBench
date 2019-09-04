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
typedef  size_t u8 ;
struct hideep_ts {size_t* xfer_buf; int /*<<< orphan*/  input_dev; int /*<<< orphan*/ * key_codes; TYPE_1__* client; } ;
struct hideep_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t HIDEEP_KEY_EVENT_INDEX ; 
 size_t HIDEEP_KEY_IDX_MASK ; 
 int /*<<< orphan*/  HIDEEP_KEY_MAX ; 
 size_t HIDEEP_KEY_PRESSED_MASK ; 
 int /*<<< orphan*/  HIDEEP_MT_MAX ; 
 size_t HIDEEP_TOUCH_EVENT_INDEX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  hideep_report_slot (int /*<<< orphan*/ ,struct hideep_event const*) ; 
 int /*<<< orphan*/  input_mt_sync_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hideep_parse_and_report(struct hideep_ts *ts)
{
	const struct hideep_event *events =
			(void *)&ts->xfer_buf[HIDEEP_TOUCH_EVENT_INDEX];
	const u8 *keys = &ts->xfer_buf[HIDEEP_KEY_EVENT_INDEX];
	int touch_count = ts->xfer_buf[0];
	int key_count = ts->xfer_buf[1] & 0x0f;
	int lpm_count = ts->xfer_buf[1] & 0xf0;
	int i;

	/* get touch event count */
	dev_dbg(&ts->client->dev, "mt = %d, key = %d, lpm = %02x",
		touch_count, key_count, lpm_count);

	touch_count = min(touch_count, HIDEEP_MT_MAX);
	for (i = 0; i < touch_count; i++)
		hideep_report_slot(ts->input_dev, events + i);

	key_count = min(key_count, HIDEEP_KEY_MAX);
	for (i = 0; i < key_count; i++) {
		u8 key_data = keys[i * 2];

		input_report_key(ts->input_dev,
				 ts->key_codes[key_data & HIDEEP_KEY_IDX_MASK],
				 key_data & HIDEEP_KEY_PRESSED_MASK);
	}

	input_mt_sync_frame(ts->input_dev);
	input_sync(ts->input_dev);
}