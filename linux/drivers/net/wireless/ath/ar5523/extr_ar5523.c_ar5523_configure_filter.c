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
typedef  int u32 ;
struct ieee80211_hw {struct ar5523* priv; } ;
struct ar5523 {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 unsigned int AR5523_SUPPORTED_FILTERS ; 
 int /*<<< orphan*/  UATH_FILTER_OP_INIT ; 
 int /*<<< orphan*/  UATH_FILTER_OP_SET ; 
 int UATH_FILTER_RX_BCAST ; 
 int UATH_FILTER_RX_BEACON ; 
 int UATH_FILTER_RX_MCAST ; 
 int UATH_FILTER_RX_PROM ; 
 int UATH_FILTER_RX_UCAST ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*) ; 
 int /*<<< orphan*/  ar5523_flush_tx (struct ar5523*) ; 
 int /*<<< orphan*/  ar5523_set_rxfilter (struct ar5523*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ar5523_configure_filter(struct ieee80211_hw *hw,
				    unsigned int changed_flags,
				    unsigned int *total_flags,
				    u64 multicast)
{
	struct ar5523 *ar = hw->priv;
	u32 filter = 0;

	ar5523_dbg(ar, "configure_filter called\n");
	mutex_lock(&ar->mutex);
	ar5523_flush_tx(ar);

	*total_flags &= AR5523_SUPPORTED_FILTERS;

	/* The filters seems strange. UATH_FILTER_RX_BCAST and
	 * UATH_FILTER_RX_MCAST does not result in those frames being RXed.
	 * The only way I have found to get [mb]cast frames seems to be
	 * to set UATH_FILTER_RX_PROM. */
	filter |= UATH_FILTER_RX_UCAST | UATH_FILTER_RX_MCAST |
		  UATH_FILTER_RX_BCAST | UATH_FILTER_RX_BEACON |
		  UATH_FILTER_RX_PROM;

	ar5523_set_rxfilter(ar, 0, UATH_FILTER_OP_INIT);
	ar5523_set_rxfilter(ar, filter, UATH_FILTER_OP_SET);

	mutex_unlock(&ar->mutex);
}