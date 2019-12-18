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
struct sja1105_private {int /*<<< orphan*/  ptp_lock; int /*<<< orphan*/  tstamp_tc; } ;
struct ptp_clock_info {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sja1105_private* ptp_to_sja1105 (struct ptp_clock_info*) ; 
 int /*<<< orphan*/  timecounter_adjtime (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sja1105_ptp_adjtime(struct ptp_clock_info *ptp, s64 delta)
{
	struct sja1105_private *priv = ptp_to_sja1105(ptp);

	mutex_lock(&priv->ptp_lock);
	timecounter_adjtime(&priv->tstamp_tc, delta);
	mutex_unlock(&priv->ptp_lock);

	return 0;
}