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
struct wl1251 {int dummy; } ;
struct acx_conn_monit_params {int /*<<< orphan*/  bss_lose_timeout; int /*<<< orphan*/  synch_fail_thold; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_CONN_MONIT_PARAMS ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NO_BEACON_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  SYNCH_FAIL_DEFAULT_THRESHOLD ; 
 int /*<<< orphan*/  kfree (struct acx_conn_monit_params*) ; 
 struct acx_conn_monit_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_conn_monit_params*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_conn_monit_params(struct wl1251 *wl)
{
	struct acx_conn_monit_params *acx;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx connection monitor parameters");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx)
		return -ENOMEM;

	acx->synch_fail_thold = SYNCH_FAIL_DEFAULT_THRESHOLD;
	acx->bss_lose_timeout = NO_BEACON_DEFAULT_TIMEOUT;

	ret = wl1251_cmd_configure(wl, ACX_CONN_MONIT_PARAMS,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1251_warning("failed to set connection monitor "
			       "parameters: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}