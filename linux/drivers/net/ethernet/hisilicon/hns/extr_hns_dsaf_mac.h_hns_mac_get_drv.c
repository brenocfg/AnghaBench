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
struct mac_driver {int dummy; } ;
struct TYPE_2__ {scalar_t__ mac; } ;
struct hns_mac_cb {TYPE_1__ priv; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mac_driver *hns_mac_get_drv(
	const struct hns_mac_cb *mac_cb)
{
	return (struct mac_driver *)(mac_cb->priv.mac);
}