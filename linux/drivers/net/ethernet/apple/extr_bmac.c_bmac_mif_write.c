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
 int /*<<< orphan*/  MIFCSR ; 
 int /*<<< orphan*/  MIFDELAY ; 
 int /*<<< orphan*/  bmac_mif_writebits (struct net_device*,int,int) ; 
 int /*<<< orphan*/  bmwrite (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bmac_mif_write(struct net_device *dev, unsigned int addr, unsigned int val)
{
	bmwrite(dev, MIFCSR, 4);
	MIFDELAY;
	bmac_mif_writebits(dev, ~0U, 32);
	bmac_mif_writebits(dev, 5, 4);
	bmac_mif_writebits(dev, addr, 10);
	bmac_mif_writebits(dev, 2, 2);
	bmac_mif_writebits(dev, val, 16);
	bmac_mif_writebits(dev, 3, 2);
}