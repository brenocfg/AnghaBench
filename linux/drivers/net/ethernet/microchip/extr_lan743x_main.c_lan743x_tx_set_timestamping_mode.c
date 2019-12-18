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
struct lan743x_tx {int /*<<< orphan*/  ts_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_TS_FLAG_ONE_STEP_SYNC ; 
 int /*<<< orphan*/  TX_TS_FLAG_TIMESTAMPING_ENABLED ; 

void lan743x_tx_set_timestamping_mode(struct lan743x_tx *tx,
				      bool enable_timestamping,
				      bool enable_onestep_sync)
{
	if (enable_timestamping)
		tx->ts_flags |= TX_TS_FLAG_TIMESTAMPING_ENABLED;
	else
		tx->ts_flags &= ~TX_TS_FLAG_TIMESTAMPING_ENABLED;
	if (enable_onestep_sync)
		tx->ts_flags |= TX_TS_FLAG_ONE_STEP_SYNC;
	else
		tx->ts_flags &= ~TX_TS_FLAG_ONE_STEP_SYNC;
}