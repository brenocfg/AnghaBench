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
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct board_info {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARDNAME ; 
 int /*<<< orphan*/  DRV_VERSION ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct board_info* to_dm9000_board (struct net_device*) ; 
 TYPE_1__* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm9000_get_drvinfo(struct net_device *dev,
			       struct ethtool_drvinfo *info)
{
	struct board_info *dm = to_dm9000_board(dev);

	strlcpy(info->driver, CARDNAME, sizeof(info->driver));
	strlcpy(info->version, DRV_VERSION, sizeof(info->version));
	strlcpy(info->bus_info, to_platform_device(dm->dev)->name,
		sizeof(info->bus_info));
}