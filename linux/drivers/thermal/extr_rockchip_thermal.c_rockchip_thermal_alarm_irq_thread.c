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
struct rockchip_thermal_data {TYPE_1__* sensors; TYPE_3__* chip; int /*<<< orphan*/  regs; TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int chn_num; int /*<<< orphan*/  (* irq_ack ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  tzd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_device_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rockchip_thermal_alarm_irq_thread(int irq, void *dev)
{
	struct rockchip_thermal_data *thermal = dev;
	int i;

	dev_dbg(&thermal->pdev->dev, "thermal alarm\n");

	thermal->chip->irq_ack(thermal->regs);

	for (i = 0; i < thermal->chip->chn_num; i++)
		thermal_zone_device_update(thermal->sensors[i].tzd,
					   THERMAL_EVENT_UNSPECIFIED);

	return IRQ_HANDLED;
}