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
struct em28xx_IR {int /*<<< orphan*/  polling; int /*<<< orphan*/  work; } ;
struct em28xx {int /*<<< orphan*/  button_polling_interval; int /*<<< orphan*/  buttons_query_work; scalar_t__ num_button_polling_addresses; TYPE_1__* intf; scalar_t__ is_audio_only; struct em28xx_IR* ir; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em28xx_ir_resume(struct em28xx *dev)
{
	struct em28xx_IR *ir = dev->ir;

	if (dev->is_audio_only)
		return 0;

	dev_info(&dev->intf->dev, "Resuming input extension\n");
	/*
	 * if suspend calls ir_raw_event_unregister(), the should call
	 * ir_raw_event_register()
	 */
	if (ir)
		schedule_delayed_work(&ir->work, msecs_to_jiffies(ir->polling));
	if (dev->num_button_polling_addresses)
		schedule_delayed_work(&dev->buttons_query_work,
				      msecs_to_jiffies(dev->button_polling_interval));
	return 0;
}