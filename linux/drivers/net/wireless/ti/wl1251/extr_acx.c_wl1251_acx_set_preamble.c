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
struct acx_preamble {int preamble; } ;
typedef  enum acx_preamble_type { ____Placeholder_acx_preamble_type } acx_preamble_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_PREAMBLE_TYPE ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_preamble*) ; 
 struct acx_preamble* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_preamble*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_set_preamble(struct wl1251 *wl, enum acx_preamble_type preamble)
{
	struct acx_preamble *acx;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx_set_preamble");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx)
		return -ENOMEM;

	acx->preamble = preamble;

	ret = wl1251_cmd_configure(wl, ACX_PREAMBLE_TYPE, acx, sizeof(*acx));
	if (ret < 0) {
		wl1251_warning("Setting of preamble failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}