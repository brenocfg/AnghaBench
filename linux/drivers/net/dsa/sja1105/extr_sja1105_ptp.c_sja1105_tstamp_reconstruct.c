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
typedef  int u64 ;
struct sja1105_private {TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  ptp_ts_bits; } ;

/* Variables and functions */
 int CYCLECOUNTER_MASK (int /*<<< orphan*/ ) ; 

u64 sja1105_tstamp_reconstruct(struct sja1105_private *priv, u64 now,
			       u64 ts_partial)
{
	u64 partial_tstamp_mask = CYCLECOUNTER_MASK(priv->info->ptp_ts_bits);
	u64 ts_reconstructed;

	ts_reconstructed = (now & ~partial_tstamp_mask) | ts_partial;

	/* Check lower bits of current cycle counter against the timestamp.
	 * If the current cycle counter is lower than the partial timestamp,
	 * then wraparound surely occurred and must be accounted for.
	 */
	if ((now & partial_tstamp_mask) <= ts_partial)
		ts_reconstructed -= (partial_tstamp_mask + 1);

	return ts_reconstructed;
}