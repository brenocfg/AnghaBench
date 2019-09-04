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
struct nic {scalar_t__ eeprom; } ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {size_t offset; int /*<<< orphan*/  len; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  E100_EEPROM_MAGIC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int e100_get_eeprom(struct net_device *netdev,
	struct ethtool_eeprom *eeprom, u8 *bytes)
{
	struct nic *nic = netdev_priv(netdev);

	eeprom->magic = E100_EEPROM_MAGIC;
	memcpy(bytes, &((u8 *)nic->eeprom)[eeprom->offset], eeprom->len);

	return 0;
}