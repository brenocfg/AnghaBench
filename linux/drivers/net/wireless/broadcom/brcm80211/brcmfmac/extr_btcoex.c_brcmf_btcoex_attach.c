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
struct brcmf_cfg80211_info {struct brcmf_btcoex_info* btcoex; } ;
struct brcmf_btcoex_info {int timer_on; int saved_regs_part1; int saved_regs_part2; int /*<<< orphan*/  work; struct brcmf_cfg80211_info* cfg; int /*<<< orphan*/  timer; int /*<<< orphan*/  timeout; int /*<<< orphan*/  bt_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_BTCOEX_OPPR_WIN_TIME ; 
 int /*<<< orphan*/  BRCMF_BT_DHCP_IDLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_btcoex_handler ; 
 int /*<<< orphan*/  brcmf_btcoex_timerfunc ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 struct brcmf_btcoex_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int brcmf_btcoex_attach(struct brcmf_cfg80211_info *cfg)
{
	struct brcmf_btcoex_info *btci = NULL;
	brcmf_dbg(TRACE, "enter\n");

	btci = kmalloc(sizeof(struct brcmf_btcoex_info), GFP_KERNEL);
	if (!btci)
		return -ENOMEM;

	btci->bt_state = BRCMF_BT_DHCP_IDLE;

	/* Set up timer for BT  */
	btci->timer_on = false;
	btci->timeout = BRCMF_BTCOEX_OPPR_WIN_TIME;
	timer_setup(&btci->timer, brcmf_btcoex_timerfunc, 0);
	btci->cfg = cfg;
	btci->saved_regs_part1 = false;
	btci->saved_regs_part2 = false;

	INIT_WORK(&btci->work, brcmf_btcoex_handler);

	cfg->btcoex = btci;
	return 0;
}