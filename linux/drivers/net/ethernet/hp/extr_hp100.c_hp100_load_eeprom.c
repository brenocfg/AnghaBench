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
typedef  int u_short ;
struct net_device {int base_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_CTRL ; 
 int /*<<< orphan*/  HP100_EEPROM_LOAD ; 
 int HP100_EE_LOAD ; 
 int /*<<< orphan*/  OPTION_MSW ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  hp100_andw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hp100_inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_orw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hp100_load_eeprom(struct net_device *dev, u_short probe_ioaddr)
{
	int i;
	int ioaddr = probe_ioaddr > 0 ? probe_ioaddr : dev->base_addr;

#ifdef HP100_DEBUG_B
	hp100_outw(0x4222, TRACE);
#endif

	hp100_page(EEPROM_CTRL);
	hp100_andw(~HP100_EEPROM_LOAD, EEPROM_CTRL);
	hp100_orw(HP100_EEPROM_LOAD, EEPROM_CTRL);
	for (i = 0; i < 10000; i++)
		if (!(hp100_inb(OPTION_MSW) & HP100_EE_LOAD))
			return;
	printk("hp100: %s: hp100_load_eeprom - timeout\n", dev->name);
}