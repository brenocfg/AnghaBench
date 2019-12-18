#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* msg; int /*<<< orphan*/  complete; } ;
struct TYPE_4__ {int curr_bank; int next_bank; } ;
struct sdw_bus {TYPE_2__ defer_msg; TYPE_1__ params; int /*<<< orphan*/  dev; int /*<<< orphan*/  bank_switch_timeout; int /*<<< orphan*/  multi_link; } ;
struct TYPE_6__ {struct TYPE_6__* buf; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdw_ml_sync_bank_switch(struct sdw_bus *bus)
{
	unsigned long time_left;

	if (!bus->multi_link)
		return 0;

	/* Wait for completion of transfer */
	time_left = wait_for_completion_timeout(&bus->defer_msg.complete,
						bus->bank_switch_timeout);

	if (!time_left) {
		dev_err(bus->dev, "Controller Timed out on bank switch\n");
		return -ETIMEDOUT;
	}

	bus->params.curr_bank = !bus->params.curr_bank;
	bus->params.next_bank = !bus->params.next_bank;

	if (bus->defer_msg.msg) {
		kfree(bus->defer_msg.msg->buf);
		kfree(bus->defer_msg.msg);
	}

	return 0;
}