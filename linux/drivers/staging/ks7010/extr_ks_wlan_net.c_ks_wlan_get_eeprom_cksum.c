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
struct ks_wlan_private {int /*<<< orphan*/  eeprom_checksum; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_get_eeprom_cksum(struct net_device *dev,
				    struct iw_request_info *info, __u32 *uwrq,
				    char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	*uwrq = priv->eeprom_checksum;
	return 0;
}