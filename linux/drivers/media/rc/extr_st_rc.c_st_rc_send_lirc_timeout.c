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
struct rc_dev {int /*<<< orphan*/  timeout; } ;
struct ir_raw_event {int timeout; int /*<<< orphan*/  duration; } ;

/* Variables and functions */
 int /*<<< orphan*/  ir_raw_event_store (struct rc_dev*,struct ir_raw_event*) ; 

__attribute__((used)) static void st_rc_send_lirc_timeout(struct rc_dev *rdev)
{
	struct ir_raw_event ev = { .timeout = true, .duration = rdev->timeout };
	ir_raw_event_store(rdev, &ev);
}