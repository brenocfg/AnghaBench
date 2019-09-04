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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int /*<<< orphan*/  len; int /*<<< orphan*/  offset; } ;
struct bnx2 {int dummy; } ;

/* Variables and functions */
 int bnx2_nvram_write (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
bnx2_set_eeprom(struct net_device *dev, struct ethtool_eeprom *eeprom,
		u8 *eebuf)
{
	struct bnx2 *bp = netdev_priv(dev);
	int rc;

	/* parameters already validated in ethtool_set_eeprom */

	rc = bnx2_nvram_write(bp, eeprom->offset, eebuf, eeprom->len);

	return rc;
}