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
struct seq_file {int dummy; } ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exhalbtc_display_bt_coex_info (struct btc_coexist*,struct seq_file*) ; 
 struct btc_coexist* rtl_btc_coexist (struct rtl_priv*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

void rtl_btc_display_bt_coex_info(struct rtl_priv *rtlpriv, struct seq_file *m)
{
	struct btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	if (!btcoexist) {
		seq_puts(m, "btc_coexist context is NULL!\n");
		return;
	}

	exhalbtc_display_bt_coex_info(btcoexist, m);
}