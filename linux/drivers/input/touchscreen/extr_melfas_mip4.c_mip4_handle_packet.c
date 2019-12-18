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
struct mip4_ts {int event_format; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MIP4_EVENT_INPUT_TYPE_KEY 129 
#define  MIP4_EVENT_INPUT_TYPE_SCREEN 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mip4_report_keys (struct mip4_ts*,int*) ; 
 int /*<<< orphan*/  mip4_report_touch (struct mip4_ts*,int*) ; 

__attribute__((used)) static int mip4_handle_packet(struct mip4_ts *ts, u8 *packet)
{
	u8 type;

	switch (ts->event_format) {
	case 0:
	case 1:
		type = (packet[0] & 0x40) >> 6;
		break;

	case 3:
		type = (packet[0] & 0xF0) >> 4;
		break;

	default:
		/* Should not happen unless we have corrupted firmware */
		return -EINVAL;
	}

	dev_dbg(&ts->client->dev, "Type: %d\n", type);

	/* Report input event */
	switch (type) {
	case MIP4_EVENT_INPUT_TYPE_KEY:
		mip4_report_keys(ts, packet);
		break;

	case MIP4_EVENT_INPUT_TYPE_SCREEN:
		mip4_report_touch(ts, packet);
		break;

	default:
		dev_err(&ts->client->dev, "Unknown event type: %d\n", type);
		break;
	}

	return 0;
}