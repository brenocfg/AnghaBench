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
 int /*<<< orphan*/  bmwrite (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bmac_mif_writebits(struct net_device *dev, unsigned int val, int nb)
{
	int b;

	while (--nb >= 0) {
		b = (val & (1 << nb))? 6: 4;
		bmwrite(dev, MIFCSR, b);
		MIFDELAY;
		bmwrite(dev, MIFCSR, b|1);
		MIFDELAY;
	}
}