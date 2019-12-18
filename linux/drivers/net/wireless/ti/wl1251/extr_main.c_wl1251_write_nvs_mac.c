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
struct wl1251 {int /*<<< orphan*/ * mac_addr; int /*<<< orphan*/ * nvs; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int NVS_OFF_MAC_DATA ; 
 int wl1251_check_nvs_mac (struct wl1251*) ; 

__attribute__((used)) static int wl1251_write_nvs_mac(struct wl1251 *wl)
{
	int i, ret;

	ret = wl1251_check_nvs_mac(wl);
	if (ret)
		return ret;

	/* MAC is stored in reverse order */
	for (i = 0; i < ETH_ALEN; i++)
		wl->nvs[NVS_OFF_MAC_DATA + i] = wl->mac_addr[ETH_ALEN - i - 1];

	return 0;
}