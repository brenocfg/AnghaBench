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
struct brcmstb_thermal_priv {int /*<<< orphan*/  thermal; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TMON_TRIP_TYPE_HIGH ; 
 int /*<<< orphan*/  TMON_TRIP_TYPE_LOW ; 
 int avs_tmon_get_intr_temp (struct brcmstb_thermal_priv*) ; 
 int avs_tmon_get_trip_temp (struct brcmstb_thermal_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avs_tmon_trip_enable (struct brcmstb_thermal_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  thermal_zone_device_update (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t brcmstb_tmon_irq_thread(int irq, void *data)
{
	struct brcmstb_thermal_priv *priv = data;
	int low, high, intr;

	low = avs_tmon_get_trip_temp(priv, TMON_TRIP_TYPE_LOW);
	high = avs_tmon_get_trip_temp(priv, TMON_TRIP_TYPE_HIGH);
	intr = avs_tmon_get_intr_temp(priv);

	dev_dbg(priv->dev, "low/intr/high: %d/%d/%d\n",
			low, intr, high);

	/* Disable high-temp until next threshold shift */
	if (intr >= high)
		avs_tmon_trip_enable(priv, TMON_TRIP_TYPE_HIGH, 0);
	/* Disable low-temp until next threshold shift */
	if (intr <= low)
		avs_tmon_trip_enable(priv, TMON_TRIP_TYPE_LOW, 0);

	/*
	 * Notify using the interrupt temperature, in case the temperature
	 * changes before it can next be read out
	 */
	thermal_zone_device_update(priv->thermal, intr);

	return IRQ_HANDLED;
}