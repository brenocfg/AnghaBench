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
struct wl18xx_acx_clear_statistics {int dummy; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_CLEAR_STATISTICS ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl18xx_acx_clear_statistics*) ; 
 struct wl18xx_acx_clear_statistics* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl18xx_acx_clear_statistics*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl18xx_acx_clear_statistics(struct wl1271 *wl)
{
	struct wl18xx_acx_clear_statistics *acx;
	int ret = 0;

	wl1271_debug(DEBUG_ACX, "acx clear statistics");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	ret = wl1271_cmd_configure(wl, ACX_CLEAR_STATISTICS, acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("failed to clear firmware statistics: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}