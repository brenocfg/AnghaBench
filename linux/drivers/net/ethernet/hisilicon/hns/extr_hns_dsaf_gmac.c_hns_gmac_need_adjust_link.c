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
struct mac_driver {struct hns_mac_cb* mac_cb; } ;
struct hns_mac_cb {int speed; int half_duplex; } ;
typedef  enum mac_speed { ____Placeholder_mac_speed } mac_speed ;

/* Variables and functions */

__attribute__((used)) static bool hns_gmac_need_adjust_link(void *mac_drv, enum mac_speed speed,
				      int duplex)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	struct hns_mac_cb *mac_cb = drv->mac_cb;

	return (mac_cb->speed != speed) ||
		(mac_cb->half_duplex == duplex);
}