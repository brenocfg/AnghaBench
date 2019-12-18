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
struct wl1251_acx_arp_filter {int enable; int /*<<< orphan*/  address; int /*<<< orphan*/  version; } ;
struct wl1251 {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_ARP_IP_FILTER ; 
 int /*<<< orphan*/  ACX_IPV4_ADDR_SIZE ; 
 int /*<<< orphan*/  ACX_IPV4_VERSION ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1251_acx_arp_filter*) ; 
 struct wl1251_acx_arp_filter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct wl1251_acx_arp_filter*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_arp_ip_filter(struct wl1251 *wl, bool enable, __be32 address)
{
	struct wl1251_acx_arp_filter *acx;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx arp ip filter, enable: %d", enable);

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx)
		return -ENOMEM;

	acx->version = ACX_IPV4_VERSION;
	acx->enable = enable;

	if (enable)
		memcpy(acx->address, &address, ACX_IPV4_ADDR_SIZE);

	ret = wl1251_cmd_configure(wl, ACX_ARP_IP_FILTER,
				   acx, sizeof(*acx));
	if (ret < 0)
		wl1251_warning("failed to set arp ip filter: %d", ret);

	kfree(acx);
	return ret;
}