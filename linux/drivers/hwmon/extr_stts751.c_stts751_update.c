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
struct stts751_priv {size_t interval; int data_valid; scalar_t__ last_update; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stts751_intervals ; 
 int stts751_update_alert (struct stts751_priv*) ; 
 int stts751_update_temp (struct stts751_priv*) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int stts751_update(struct stts751_priv *priv)
{
	int ret;
	int cache_time = msecs_to_jiffies(stts751_intervals[priv->interval]);

	if (time_after(jiffies,	priv->last_update + cache_time) ||
	    !priv->data_valid) {
		ret = stts751_update_temp(priv);
		if (ret)
			return ret;

		ret = stts751_update_alert(priv);
		if (ret)
			return ret;
		priv->data_valid = true;
		priv->last_update = jiffies;
	}

	return 0;
}