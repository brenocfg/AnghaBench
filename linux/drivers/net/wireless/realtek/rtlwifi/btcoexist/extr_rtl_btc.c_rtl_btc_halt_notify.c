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
struct rtl_priv {int dummy; } ;
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exhalbtc_halt_notify (struct btc_coexist*) ; 
 struct btc_coexist* rtl_btc_coexist (struct rtl_priv*) ; 

void rtl_btc_halt_notify(struct rtl_priv *rtlpriv)
{
	struct btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	if (!btcoexist)
		return;

	exhalbtc_halt_notify(btcoexist);
}