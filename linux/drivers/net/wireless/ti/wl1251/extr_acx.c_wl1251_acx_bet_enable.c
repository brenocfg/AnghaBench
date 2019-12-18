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
struct wl1251_acx_bet_enable {int enable; int /*<<< orphan*/  max_consecutive; } ;
struct wl1251 {int dummy; } ;
typedef  enum wl1251_acx_bet_mode { ____Placeholder_wl1251_acx_bet_mode } wl1251_acx_bet_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_BET_ENABLE ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1251_acx_bet_enable*) ; 
 struct wl1251_acx_bet_enable* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct wl1251_acx_bet_enable*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_bet_enable(struct wl1251 *wl, enum wl1251_acx_bet_mode mode,
			  u8 max_consecutive)
{
	struct wl1251_acx_bet_enable *acx;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx bet enable");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx)
		return -ENOMEM;

	acx->enable = mode;
	acx->max_consecutive = max_consecutive;

	ret = wl1251_cmd_configure(wl, ACX_BET_ENABLE, acx, sizeof(*acx));
	if (ret < 0) {
		wl1251_warning("wl1251 acx bet enable failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}