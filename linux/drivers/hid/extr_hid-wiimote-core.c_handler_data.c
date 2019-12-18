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
struct TYPE_2__ {int cmd_read_size; scalar_t__ cmd_read_buf; } ;
struct wiimote_data {TYPE_1__ state; } ;
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  WIIPROTO_REQ_RMEM ; 
 int /*<<< orphan*/  handler_keys (struct wiimote_data*,int const*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int const*,int) ; 
 int /*<<< orphan*/  wiimote_cmd_complete (struct wiimote_data*) ; 
 scalar_t__ wiimote_cmd_pending (struct wiimote_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void handler_data(struct wiimote_data *wdata, const __u8 *payload)
{
	__u16 offset = payload[3] << 8 | payload[4];
	__u8 size = (payload[2] >> 4) + 1;
	__u8 err = payload[2] & 0x0f;

	handler_keys(wdata, payload);

	if (wiimote_cmd_pending(wdata, WIIPROTO_REQ_RMEM, offset)) {
		if (err)
			size = 0;
		else if (size > wdata->state.cmd_read_size)
			size = wdata->state.cmd_read_size;

		wdata->state.cmd_read_size = size;
		if (wdata->state.cmd_read_buf)
			memcpy(wdata->state.cmd_read_buf, &payload[5], size);
		wiimote_cmd_complete(wdata);
	}
}