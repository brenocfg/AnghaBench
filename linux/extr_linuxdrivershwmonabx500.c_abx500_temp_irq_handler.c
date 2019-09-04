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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_handler ) (int,struct abx500_temp*) ;} ;
struct abx500_temp {TYPE_1__ ops; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct abx500_temp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (int,struct abx500_temp*) ; 

__attribute__((used)) static irqreturn_t abx500_temp_irq_handler(int irq, void *irq_data)
{
	struct platform_device *pdev = irq_data;
	struct abx500_temp *data = platform_get_drvdata(pdev);

	data->ops.irq_handler(irq, data);
	return IRQ_HANDLED;
}