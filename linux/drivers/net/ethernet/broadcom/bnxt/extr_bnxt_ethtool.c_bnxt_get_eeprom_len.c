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
struct bnxt {int dummy; } ;

/* Variables and functions */
 scalar_t__ BNXT_VF (struct bnxt*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_get_eeprom_len(struct net_device *dev)
{
	struct bnxt *bp = netdev_priv(dev);

	if (BNXT_VF(bp))
		return 0;

	/* The -1 return value allows the entire 32-bit range of offsets to be
	 * passed via the ethtool command-line utility.
	 */
	return -1;
}