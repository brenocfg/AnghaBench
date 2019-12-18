#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wl1251 {int dummy; } ;
struct acx_rate_policy {int rate_class_cnt; TYPE_1__* rate_class; } ;
struct TYPE_2__ {scalar_t__ aflags; void* long_retry_limit; void* short_retry_limit; void* enabled_rates; } ;

/* Variables and functions */
 void* ACX_RATE_MASK_UNSPECIFIED ; 
 int /*<<< orphan*/  ACX_RATE_POLICY ; 
 void* ACX_RATE_RETRY_LIMIT ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_rate_policy*) ; 
 struct acx_rate_policy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_rate_policy*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_rate_policies(struct wl1251 *wl)
{
	struct acx_rate_policy *acx;
	int ret = 0;

	wl1251_debug(DEBUG_ACX, "acx rate policies");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx)
		return -ENOMEM;

	/* configure one default (one-size-fits-all) rate class */
	acx->rate_class_cnt = 2;
	acx->rate_class[0].enabled_rates = ACX_RATE_MASK_UNSPECIFIED;
	acx->rate_class[0].short_retry_limit = ACX_RATE_RETRY_LIMIT;
	acx->rate_class[0].long_retry_limit = ACX_RATE_RETRY_LIMIT;
	acx->rate_class[0].aflags = 0;

	/* no-retry rate class */
	acx->rate_class[1].enabled_rates = ACX_RATE_MASK_UNSPECIFIED;
	acx->rate_class[1].short_retry_limit = 0;
	acx->rate_class[1].long_retry_limit = 0;
	acx->rate_class[1].aflags = 0;

	ret = wl1251_cmd_configure(wl, ACX_RATE_POLICY, acx, sizeof(*acx));
	if (ret < 0) {
		wl1251_warning("Setting of rate policies failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}