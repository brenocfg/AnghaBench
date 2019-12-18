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
struct sja1105_private {int /*<<< orphan*/ * clock; int /*<<< orphan*/  refresh_work; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ *) ; 

void sja1105_ptp_clock_unregister(struct sja1105_private *priv)
{
	if (IS_ERR_OR_NULL(priv->clock))
		return;

	cancel_delayed_work_sync(&priv->refresh_work);
	ptp_clock_unregister(priv->clock);
	priv->clock = NULL;
}