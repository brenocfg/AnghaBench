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

/* Variables and functions */
 int /*<<< orphan*/  SROMCSR ; 
 int /*<<< orphan*/  bmac_clock_in_bit (struct net_device*,unsigned short) ; 
 unsigned short bmac_clock_out_bit (struct net_device*) ; 
 int /*<<< orphan*/  bmwrite (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned short
read_srom(struct net_device *dev, unsigned int addr, unsigned int addr_len)
{
	unsigned short data, val;
	int i;

	/* send out the address we want to read from */
	for (i = 0; i < addr_len; i++)	{
		val = addr >> (addr_len-i-1);
		bmac_clock_in_bit(dev, val & 1);
	}

	/* Now read in the 16-bit data */
	data = 0;
	for (i = 0; i < 16; i++)	{
		val = bmac_clock_out_bit(dev);
		data <<= 1;
		data |= val;
	}
	bmwrite(dev, SROMCSR, 0);

	return data;
}