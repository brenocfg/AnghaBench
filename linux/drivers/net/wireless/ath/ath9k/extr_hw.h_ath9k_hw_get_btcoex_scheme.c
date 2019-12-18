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
struct ath_hw {int dummy; } ;
typedef  enum ath_btcoex_scheme { ____Placeholder_ath_btcoex_scheme } ath_btcoex_scheme ;

/* Variables and functions */
 int ATH_BTCOEX_CFG_NONE ; 

__attribute__((used)) static inline enum ath_btcoex_scheme
ath9k_hw_get_btcoex_scheme(struct ath_hw *ah)
{
	return ATH_BTCOEX_CFG_NONE;
}