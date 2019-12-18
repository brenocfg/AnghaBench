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
typedef  int /*<<< orphan*/  u64 ;
struct timespec64 {int dummy; } ;
struct sja1105_private {int /*<<< orphan*/  ptp_lock; int /*<<< orphan*/  tstamp_cc; int /*<<< orphan*/  tstamp_tc; } ;
struct ptp_clock_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sja1105_private* ptp_to_sja1105 (struct ptp_clock_info*) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timespec64_to_ns (struct timespec64 const*) ; 

__attribute__((used)) static int sja1105_ptp_settime(struct ptp_clock_info *ptp,
			       const struct timespec64 *ts)
{
	struct sja1105_private *priv = ptp_to_sja1105(ptp);
	u64 ns = timespec64_to_ns(ts);

	mutex_lock(&priv->ptp_lock);
	timecounter_init(&priv->tstamp_tc, &priv->tstamp_cc, ns);
	mutex_unlock(&priv->ptp_lock);

	return 0;
}