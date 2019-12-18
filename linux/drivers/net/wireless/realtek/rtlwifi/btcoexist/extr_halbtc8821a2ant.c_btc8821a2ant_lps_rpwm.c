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
typedef  void* u8 ;
struct btc_coexist {int dummy; } ;
struct TYPE_2__ {scalar_t__ cur_lps; scalar_t__ cur_rpwm; scalar_t__ pre_lps; scalar_t__ pre_rpwm; } ;

/* Variables and functions */
 int /*<<< orphan*/  btc8821a2ant_set_lps_rpwm (struct btc_coexist*,void*,void*) ; 
 TYPE_1__* coex_dm ; 

__attribute__((used)) static void btc8821a2ant_lps_rpwm(struct btc_coexist *btcoexist,
				  bool force_exec, u8 lps_val, u8 rpwm_val)
{
	coex_dm->cur_lps = lps_val;
	coex_dm->cur_rpwm = rpwm_val;

	if (!force_exec) {
		if ((coex_dm->pre_lps == coex_dm->cur_lps) &&
		    (coex_dm->pre_rpwm == coex_dm->cur_rpwm))
			return;
	}
	btc8821a2ant_set_lps_rpwm(btcoexist, lps_val, rpwm_val);

	coex_dm->pre_lps = coex_dm->cur_lps;
	coex_dm->pre_rpwm = coex_dm->cur_rpwm;
}