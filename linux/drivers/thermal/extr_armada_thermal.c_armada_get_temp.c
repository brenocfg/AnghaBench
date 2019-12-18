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
struct armada_thermal_sensor {int /*<<< orphan*/  id; struct armada_thermal_priv* priv; } ;
struct armada_thermal_priv {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  interrupt_source; } ;

/* Variables and functions */
 int armada_read_sensor (struct armada_thermal_priv*,int*) ; 
 int armada_select_channel (struct armada_thermal_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int armada_get_temp(void *_sensor, int *temp)
{
	struct armada_thermal_sensor *sensor = _sensor;
	struct armada_thermal_priv *priv = sensor->priv;
	int ret;

	mutex_lock(&priv->update_lock);

	/* Select the desired channel */
	ret = armada_select_channel(priv, sensor->id);
	if (ret)
		goto unlock_mutex;

	/* Do the actual reading */
	ret = armada_read_sensor(priv, temp);
	if (ret)
		goto unlock_mutex;

	/*
	 * Select back the interrupt source channel from which a potential
	 * critical trip point has been set.
	 */
	ret = armada_select_channel(priv, priv->interrupt_source);

unlock_mutex:
	mutex_unlock(&priv->update_lock);

	return ret;
}