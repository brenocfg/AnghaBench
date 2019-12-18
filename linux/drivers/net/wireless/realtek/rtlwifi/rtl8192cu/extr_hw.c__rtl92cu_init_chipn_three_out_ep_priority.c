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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_HIGH ; 
 int /*<<< orphan*/  QUEUE_LOW ; 
 int /*<<< orphan*/  QUEUE_NORMAL ; 
 int /*<<< orphan*/  _rtl92c_init_chipn_reg_priority (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl92cu_init_chipn_three_out_ep_priority(struct ieee80211_hw *hw,
						      bool wmm_enable,
						      u8 queue_sel)
{
	u16 beq, bkq, viq, voq, mgtq, hiq;

	if (!wmm_enable) { /* typical setting */
		beq	= QUEUE_LOW;
		bkq	= QUEUE_LOW;
		viq	= QUEUE_NORMAL;
		voq	= QUEUE_HIGH;
		mgtq	= QUEUE_HIGH;
		hiq	= QUEUE_HIGH;
	} else { /* for WMM */
		beq	= QUEUE_LOW;
		bkq	= QUEUE_NORMAL;
		viq	= QUEUE_NORMAL;
		voq	= QUEUE_HIGH;
		mgtq	= QUEUE_HIGH;
		hiq	= QUEUE_HIGH;
	}
	_rtl92c_init_chipn_reg_priority(hw, beq, bkq, viq, voq, mgtq, hiq);
	pr_info("Tx queue select :0x%02x..\n", queue_sel);
}