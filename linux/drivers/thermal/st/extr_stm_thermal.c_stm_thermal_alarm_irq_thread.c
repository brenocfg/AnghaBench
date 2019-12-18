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
typedef  int u32 ;
struct stm_thermal_sensor {int /*<<< orphan*/  th_dev; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DTS_CIFR_OFFSET ; 
 scalar_t__ DTS_SR_OFFSET ; 
 int HIGH_THRESHOLD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int LOW_THRESHOLD ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  thermal_zone_device_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t stm_thermal_alarm_irq_thread(int irq, void *sdata)
{
	u32 value;
	struct stm_thermal_sensor *sensor = sdata;

	/* read IT reason in SR and clear flags */
	value = readl_relaxed(sensor->base + DTS_SR_OFFSET);

	if ((value & LOW_THRESHOLD) == LOW_THRESHOLD)
		writel_relaxed(LOW_THRESHOLD, sensor->base + DTS_CIFR_OFFSET);

	if ((value & HIGH_THRESHOLD) == HIGH_THRESHOLD)
		writel_relaxed(HIGH_THRESHOLD, sensor->base + DTS_CIFR_OFFSET);

	thermal_zone_device_update(sensor->th_dev, THERMAL_EVENT_UNSPECIFIED);

	return IRQ_HANDLED;
}