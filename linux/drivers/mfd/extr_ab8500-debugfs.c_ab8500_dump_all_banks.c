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
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int AB8500_NUM_BANKS ; 
 int /*<<< orphan*/  ab8500_registers_print (struct device*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 

void ab8500_dump_all_banks(struct device *dev)
{
	unsigned int i;

	dev_info(dev, "ab8500 register values:\n");

	for (i = 1; i < AB8500_NUM_BANKS; i++) {
		dev_info(dev, " bank 0x%02X:\n", i);
		ab8500_registers_print(dev, i, NULL);
	}
}