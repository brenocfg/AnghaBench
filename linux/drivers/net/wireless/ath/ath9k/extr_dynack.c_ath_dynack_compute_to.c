#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct ts_info {scalar_t__ tstamp; scalar_t__ dur; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ath_node {int /*<<< orphan*/  ackto; } ;
struct TYPE_6__ {size_t h_rb; size_t t_rb; scalar_t__* tstamp; } ;
struct TYPE_5__ {size_t h_rb; size_t t_rb; TYPE_1__* addr; struct ts_info* ts; } ;
struct ath_dynack {TYPE_3__ ack_rbf; TYPE_2__ st_rbf; scalar_t__ lto; } ;
struct ath_hw {int /*<<< orphan*/  hw; struct ath_dynack dynack; } ;
struct TYPE_4__ {int /*<<< orphan*/ * h_src; int /*<<< orphan*/ * h_dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_DYN_BUF ; 
 scalar_t__ COMPUTE_TO ; 
 int /*<<< orphan*/  DYNACK ; 
 int /*<<< orphan*/  INCR (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  ath_dynack_compute_ackto (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dynack_ewma (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ath_dynack_get_max_to (struct ath_hw*) ; 
 struct ieee80211_sta* ieee80211_find_sta_by_ifaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 

__attribute__((used)) static void ath_dynack_compute_to(struct ath_hw *ah)
{
	struct ath_dynack *da = &ah->dynack;
	u32 ackto, ack_ts, max_to;
	struct ieee80211_sta *sta;
	struct ts_info *st_ts;
	struct ath_node *an;
	u8 *dst, *src;

	rcu_read_lock();

	max_to = ath_dynack_get_max_to(ah);
	while (da->st_rbf.h_rb != da->st_rbf.t_rb &&
	       da->ack_rbf.h_rb != da->ack_rbf.t_rb) {
		ack_ts = da->ack_rbf.tstamp[da->ack_rbf.h_rb];
		st_ts = &da->st_rbf.ts[da->st_rbf.h_rb];
		dst = da->st_rbf.addr[da->st_rbf.h_rb].h_dest;
		src = da->st_rbf.addr[da->st_rbf.h_rb].h_src;

		ath_dbg(ath9k_hw_common(ah), DYNACK,
			"ack_ts %u st_ts %u st_dur %u [%u-%u]\n",
			ack_ts, st_ts->tstamp, st_ts->dur,
			da->ack_rbf.h_rb, da->st_rbf.h_rb);

		if (ack_ts > st_ts->tstamp + st_ts->dur) {
			ackto = ack_ts - st_ts->tstamp - st_ts->dur;

			if (ackto < max_to) {
				sta = ieee80211_find_sta_by_ifaddr(ah->hw, dst,
								   src);
				if (sta) {
					an = (struct ath_node *)sta->drv_priv;
					an->ackto = ath_dynack_ewma(an->ackto,
								    ackto);
					ath_dbg(ath9k_hw_common(ah), DYNACK,
						"%pM to %d [%u]\n", dst,
						an->ackto, ackto);
					if (time_is_before_jiffies(da->lto)) {
						ath_dynack_compute_ackto(ah);
						da->lto = jiffies + COMPUTE_TO;
					}
				}
				INCR(da->ack_rbf.h_rb, ATH_DYN_BUF);
			}
			INCR(da->st_rbf.h_rb, ATH_DYN_BUF);
		} else {
			INCR(da->ack_rbf.h_rb, ATH_DYN_BUF);
		}
	}

	rcu_read_unlock();
}