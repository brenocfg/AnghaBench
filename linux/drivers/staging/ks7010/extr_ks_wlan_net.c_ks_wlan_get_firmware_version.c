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
struct ks_wlan_private {scalar_t__ version_size; int /*<<< orphan*/  firmware_version; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {scalar_t__ length; } ;

/* Variables and functions */
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ks_wlan_get_firmware_version(struct net_device *dev,
					struct iw_request_info *info,
					struct iw_point *dwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	strcpy(extra, priv->firmware_version);
	dwrq->length = priv->version_size + 1;
	return 0;
}