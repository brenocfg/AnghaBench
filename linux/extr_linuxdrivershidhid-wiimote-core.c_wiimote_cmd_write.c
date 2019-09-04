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
struct TYPE_2__ {scalar_t__ cmd_err; int /*<<< orphan*/  lock; } ;
struct wiimote_data {TYPE_1__ state; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  WIIPROTO_REQ_WMEM ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wiimote_cmd_set (struct wiimote_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wiimote_cmd_wait (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiiproto_req_wreg (struct wiimote_data*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int wiimote_cmd_write(struct wiimote_data *wdata, __u32 offset,
						const __u8 *wmem, __u8 size)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wiimote_cmd_set(wdata, WIIPROTO_REQ_WMEM, 0);
	wiiproto_req_wreg(wdata, offset, wmem, size);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	ret = wiimote_cmd_wait(wdata);
	if (!ret && wdata->state.cmd_err)
		ret = -EIO;

	return ret;
}