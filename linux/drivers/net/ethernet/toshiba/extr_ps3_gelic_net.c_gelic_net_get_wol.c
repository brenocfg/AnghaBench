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
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  sopass; scalar_t__ supported; scalar_t__ wolopts; } ;

/* Variables and functions */
 scalar_t__ WAKE_MAGIC ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ps3_compare_firmware_version (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ps3_sys_manager_get_wol () ; 

__attribute__((used)) static void gelic_net_get_wol(struct net_device *netdev,
			      struct ethtool_wolinfo *wol)
{
	if (0 <= ps3_compare_firmware_version(2, 2, 0))
		wol->supported = WAKE_MAGIC;
	else
		wol->supported = 0;

	wol->wolopts = ps3_sys_manager_get_wol() ? wol->supported : 0;
	memset(&wol->sopass, 0, sizeof(wol->sopass));
}