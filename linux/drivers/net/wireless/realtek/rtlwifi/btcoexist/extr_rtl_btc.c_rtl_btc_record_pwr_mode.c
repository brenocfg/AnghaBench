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
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  pwr_mode_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 struct btc_coexist* rtl_btc_coexist (struct rtl_priv*) ; 

void rtl_btc_record_pwr_mode(struct rtl_priv *rtlpriv, u8 *buf, u8 len)
{
	struct btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);
	u8 safe_len;

	if (!btcoexist)
		return;

	safe_len = sizeof(btcoexist->pwr_mode_val);

	if (safe_len > len)
		safe_len = len;

	memcpy(btcoexist->pwr_mode_val, buf, safe_len);
}