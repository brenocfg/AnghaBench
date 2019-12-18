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
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_NORMAL_CHIP (int /*<<< orphan*/ ) ; 
 int _out_ep_mapping (struct ieee80211_hw*) ; 
 int configvernoutep (struct ieee80211_hw*) ; 
 int configvertoutep (struct ieee80211_hw*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

int  rtl8192cu_endpoint_mapping(struct ieee80211_hw *hw)
{
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	int error = 0;

	if (likely(IS_NORMAL_CHIP(rtlhal->version)))
		error = configvernoutep(hw);
	else
		error = configvertoutep(hw);
	if (error)
		goto err_out;
	error = _out_ep_mapping(hw);
	if (error)
		goto err_out;
err_out:
	return error;
}