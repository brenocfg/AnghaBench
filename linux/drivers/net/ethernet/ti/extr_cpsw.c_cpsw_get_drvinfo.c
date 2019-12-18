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
struct platform_device {char* name; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct cpsw_common {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpsw_get_drvinfo(struct net_device *ndev,
			     struct ethtool_drvinfo *info)
{
	struct cpsw_common *cpsw = ndev_to_cpsw(ndev);
	struct platform_device	*pdev = to_platform_device(cpsw->dev);

	strlcpy(info->driver, "cpsw", sizeof(info->driver));
	strlcpy(info->version, "1.0", sizeof(info->version));
	strlcpy(info->bus_info, pdev->name, sizeof(info->bus_info));
}