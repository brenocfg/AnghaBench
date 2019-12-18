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
struct TYPE_2__ {scalar_t__ cmd_err; } ;
struct wiimote_data {int /*<<< orphan*/  hdev; TYPE_1__ state; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  handler_keys (struct wiimote_data*,scalar_t__ const*) ; 
 int /*<<< orphan*/  hid_warn (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wiimote_cmd_complete (struct wiimote_data*) ; 
 scalar_t__ wiimote_cmd_pending (struct wiimote_data*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handler_return(struct wiimote_data *wdata, const __u8 *payload)
{
	__u8 err = payload[3];
	__u8 cmd = payload[2];

	handler_keys(wdata, payload);

	if (wiimote_cmd_pending(wdata, cmd, 0)) {
		wdata->state.cmd_err = err;
		wiimote_cmd_complete(wdata);
	} else if (err) {
		hid_warn(wdata->hdev, "Remote error %hhu on req %hhu\n", err,
									cmd);
	}
}