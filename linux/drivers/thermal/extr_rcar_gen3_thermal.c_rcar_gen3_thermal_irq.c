#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct rcar_gen3_thermal_priv {int num_tscs; TYPE_1__** tscs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_GEN3_IRQSTR ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 scalar_t__ rcar_gen3_thermal_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_gen3_thermal_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_device_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rcar_gen3_thermal_irq(int irq, void *data)
{
	struct rcar_gen3_thermal_priv *priv = data;
	u32 status;
	int i;

	for (i = 0; i < priv->num_tscs; i++) {
		status = rcar_gen3_thermal_read(priv->tscs[i], REG_GEN3_IRQSTR);
		rcar_gen3_thermal_write(priv->tscs[i], REG_GEN3_IRQSTR, 0);
		if (status)
			thermal_zone_device_update(priv->tscs[i]->zone,
						   THERMAL_EVENT_UNSPECIFIED);
	}

	return IRQ_HANDLED;
}