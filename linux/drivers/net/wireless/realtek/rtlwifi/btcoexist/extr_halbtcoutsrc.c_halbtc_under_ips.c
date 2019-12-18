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
struct rtl_ps_ctl {int rfpwr_state; scalar_t__ rfoff_reason; scalar_t__ inactiveps; } ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
typedef  enum rf_pwrstate { ____Placeholder_rf_pwrstate } rf_pwrstate ;

/* Variables and functions */
 int ERFON ; 
 scalar_t__ RF_CHANGE_BY_IPS ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 

__attribute__((used)) static bool halbtc_under_ips(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	enum rf_pwrstate rtstate;

	if (ppsc->inactiveps) {
		rtstate = ppsc->rfpwr_state;

		if (rtstate != ERFON &&
		    ppsc->rfoff_reason == RF_CHANGE_BY_IPS) {
			return true;
		}
	}

	return false;
}