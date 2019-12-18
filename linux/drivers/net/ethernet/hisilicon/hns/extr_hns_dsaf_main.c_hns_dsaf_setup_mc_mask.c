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
typedef  size_t u8 ;
struct dsaf_device {TYPE_1__** mac_cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  mc_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ MAC_IS_BROADCAST (size_t*) ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (size_t*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_dsaf_setup_mc_mask(struct dsaf_device *dsaf_dev,
				   u8 port_num, u8 *mask, u8 *addr)
{
	if (MAC_IS_BROADCAST(addr))
		memset(mask, 0xff, ETH_ALEN);
	else
		memcpy(mask, dsaf_dev->mac_cb[port_num]->mc_mask, ETH_ALEN);
}