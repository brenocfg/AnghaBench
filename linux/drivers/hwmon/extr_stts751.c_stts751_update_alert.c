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
struct stts751_priv {size_t interval; int alert_valid; int max_alert; int min_alert; int therm_trip; TYPE_1__* client; scalar_t__ last_alert_update; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  STTS751_REG_STATUS ; 
 int STTS751_STATUS_TRIPH ; 
 int STTS751_STATUS_TRIPL ; 
 int STTS751_STATUS_TRIPT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stts751_intervals ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int stts751_update_alert(struct stts751_priv *priv)
{
	int ret;
	bool conv_done;
	int cache_time = msecs_to_jiffies(stts751_intervals[priv->interval]);

	/*
	 * Add another 10% because if we run faster than the HW conversion
	 * rate we will end up in reporting incorrectly alarms.
	 */
	cache_time += cache_time / 10;

	ret = i2c_smbus_read_byte_data(priv->client, STTS751_REG_STATUS);
	if (ret < 0)
		return ret;

	dev_dbg(&priv->client->dev, "status reg %x\n", ret);
	conv_done = ret & (STTS751_STATUS_TRIPH | STTS751_STATUS_TRIPL);
	/*
	 * Reset the cache if the cache time expired, or if we are sure
	 * we have valid data from a device conversion, or if we know
	 * our cache has been never written.
	 *
	 * Note that when the cache has been never written the point is
	 * to correctly initialize the timestamp, rather than clearing
	 * the cache values.
	 *
	 * Note that updating the cache timestamp when we get an alarm flag
	 * is required, otherwise we could incorrectly report alarms to be zero.
	 */
	if (time_after(jiffies,	priv->last_alert_update + cache_time) ||
	    conv_done || !priv->alert_valid) {
		priv->max_alert = false;
		priv->min_alert = false;
		priv->alert_valid = true;
		priv->last_alert_update = jiffies;
		dev_dbg(&priv->client->dev, "invalidating alert cache\n");
	}

	priv->max_alert |= !!(ret & STTS751_STATUS_TRIPH);
	priv->min_alert |= !!(ret & STTS751_STATUS_TRIPL);
	priv->therm_trip = !!(ret & STTS751_STATUS_TRIPT);

	dev_dbg(&priv->client->dev, "max_alert: %d, min_alert: %d, therm_trip: %d\n",
		priv->max_alert, priv->min_alert, priv->therm_trip);

	return 0;
}