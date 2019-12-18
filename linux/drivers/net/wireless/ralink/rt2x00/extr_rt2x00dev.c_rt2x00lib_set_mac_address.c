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
typedef  int /*<<< orphan*/  u8 ;
struct rt2x00_dev {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (char const*) ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 char* of_get_mac_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_eeprom_dbg (struct rt2x00_dev*,char*,int /*<<< orphan*/ *) ; 

void rt2x00lib_set_mac_address(struct rt2x00_dev *rt2x00dev, u8 *eeprom_mac_addr)
{
	const char *mac_addr;

	mac_addr = of_get_mac_address(rt2x00dev->dev->of_node);
	if (!IS_ERR(mac_addr))
		ether_addr_copy(eeprom_mac_addr, mac_addr);

	if (!is_valid_ether_addr(eeprom_mac_addr)) {
		eth_random_addr(eeprom_mac_addr);
		rt2x00_eeprom_dbg(rt2x00dev, "MAC: %pM\n", eeprom_mac_addr);
	}
}