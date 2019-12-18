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

/* Variables and functions */
 int /*<<< orphan*/  exhalbtc_bind_bt_coex_withadapter (struct rtl_priv*) ; 
 int /*<<< orphan*/  exhalbtc_initlize_variables (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_btc_alloc_variable (struct rtl_priv*,int) ; 

void rtl_btc_init_variables(struct rtl_priv *rtlpriv)
{
	rtl_btc_alloc_variable(rtlpriv, false);

	exhalbtc_initlize_variables(rtlpriv);
	exhalbtc_bind_bt_coex_withadapter(rtlpriv);
}