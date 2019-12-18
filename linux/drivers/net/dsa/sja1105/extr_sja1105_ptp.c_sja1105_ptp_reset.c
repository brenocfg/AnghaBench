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
struct sja1105_ptp_cmd {int resptp; int /*<<< orphan*/  member_0; } ;
struct sja1105_private {int /*<<< orphan*/  ptp_lock; int /*<<< orphan*/  tstamp_cc; int /*<<< orphan*/  tstamp_tc; TYPE_1__* info; struct dsa_switch* ds; } ;
struct dsa_switch {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* ptp_cmd ) (struct sja1105_private*,struct sja1105_ptp_cmd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct sja1105_private*,struct sja1105_ptp_cmd*) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sja1105_ptp_reset(struct sja1105_private *priv)
{
	struct dsa_switch *ds = priv->ds;
	struct sja1105_ptp_cmd cmd = {0};
	int rc;

	mutex_lock(&priv->ptp_lock);

	cmd.resptp = 1;
	dev_dbg(ds->dev, "Resetting PTP clock\n");
	rc = priv->info->ptp_cmd(priv, &cmd);

	timecounter_init(&priv->tstamp_tc, &priv->tstamp_cc,
			 ktime_to_ns(ktime_get_real()));

	mutex_unlock(&priv->ptp_lock);

	return rc;
}