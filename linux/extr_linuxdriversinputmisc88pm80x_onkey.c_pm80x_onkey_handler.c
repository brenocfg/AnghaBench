#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pm80x_onkey_info {TYPE_2__* idev; int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  KEY_POWER ; 
 unsigned int PM800_ONKEY_STS1 ; 
 int /*<<< orphan*/  PM800_STATUS_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  input_report_key (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_sync (TYPE_2__*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static irqreturn_t pm80x_onkey_handler(int irq, void *data)
{
	struct pm80x_onkey_info *info = data;
	int ret = 0;
	unsigned int val;

	ret = regmap_read(info->map, PM800_STATUS_1, &val);
	if (ret < 0) {
		dev_err(info->idev->dev.parent, "failed to read status: %d\n", ret);
		return IRQ_NONE;
	}
	val &= PM800_ONKEY_STS1;

	input_report_key(info->idev, KEY_POWER, val);
	input_sync(info->idev);

	return IRQ_HANDLED;
}