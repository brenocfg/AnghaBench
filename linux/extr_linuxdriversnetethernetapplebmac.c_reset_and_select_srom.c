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
 int /*<<< orphan*/  DelayValue ; 
 int /*<<< orphan*/  SROMCSR ; 
 int /*<<< orphan*/  bmac_clock_in_bit (struct net_device*,int) ; 
 int /*<<< orphan*/  bmwrite (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reset_and_select_srom(struct net_device *dev)
{
	/* first reset */
	bmwrite(dev, SROMCSR, 0);
	udelay(DelayValue);

	/* send it the read command (110) */
	bmac_clock_in_bit(dev, 1);
	bmac_clock_in_bit(dev, 1);
	bmac_clock_in_bit(dev, 0);
}