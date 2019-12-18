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
struct wl12xx_null_data_template {int dummy; } ;
struct wl1251 {scalar_t__ bss_type; int /*<<< orphan*/  vif; int /*<<< orphan*/  hw; } ;
struct sk_buff {int len; void* data; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_IBSS ; 
 int /*<<< orphan*/  CMD_NULL_DATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* ieee80211_nullfunc_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int wl1251_cmd_template_set (struct wl1251*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

__attribute__((used)) static int wl1251_build_null_data(struct wl1251 *wl)
{
	struct sk_buff *skb = NULL;
	int size;
	void *ptr;
	int ret = -ENOMEM;

	if (wl->bss_type == BSS_TYPE_IBSS) {
		size = sizeof(struct wl12xx_null_data_template);
		ptr = NULL;
	} else {
		skb = ieee80211_nullfunc_get(wl->hw, wl->vif, false);
		if (!skb)
			goto out;
		size = skb->len;
		ptr = skb->data;
	}

	ret = wl1251_cmd_template_set(wl, CMD_NULL_DATA, ptr, size);

out:
	dev_kfree_skb(skb);
	if (ret)
		wl1251_warning("cmd buld null data failed: %d", ret);

	return ret;
}