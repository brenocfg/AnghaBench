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
struct ethtool_eeprom {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int TLAN_EEPROM_SIZE ; 
 scalar_t__ tlan_ee_read_byte (struct net_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tlan_get_eeprom(struct net_device *dev,
			   struct ethtool_eeprom *eeprom, u8 *data)
{
	int i;

	for (i = 0; i < TLAN_EEPROM_SIZE; i++)
		if (tlan_ee_read_byte(dev, i, &data[i]))
			return -EIO;

	return 0;
}