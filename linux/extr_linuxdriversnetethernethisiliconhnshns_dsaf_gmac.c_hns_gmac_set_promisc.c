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
typedef  int /*<<< orphan*/  u8 ;
struct mac_driver {TYPE_1__* mac_cb; } ;
struct TYPE_2__ {scalar_t__ mac_type; } ;

/* Variables and functions */
 scalar_t__ HNAE_PORT_DEBUG ; 
 int /*<<< orphan*/  hns_gmac_set_uc_match (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_gmac_set_promisc(void *mac_drv, u8 en)
{
	struct mac_driver *drv = mac_drv;

	if (drv->mac_cb->mac_type == HNAE_PORT_DEBUG)
		hns_gmac_set_uc_match(mac_drv, en);
}