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
struct device {int /*<<< orphan*/  of_node; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned long BIT (unsigned int) ; 
 int /*<<< orphan*/ * of_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int of_read_number (int /*<<< orphan*/  const*,int) ; 

unsigned int jz4780_nemc_num_banks(struct device *dev)
{
	const __be32 *prop;
	unsigned int bank, count = 0;
	unsigned long referenced = 0;
	int i = 0;

	while ((prop = of_get_address(dev->of_node, i++, NULL, NULL))) {
		bank = of_read_number(prop, 1);
		if (!(referenced & BIT(bank))) {
			referenced |= BIT(bank);
			count++;
		}
	}

	return count;
}