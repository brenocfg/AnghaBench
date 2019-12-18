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
struct net_device {int mem_end; scalar_t__ mem_start; } ;

/* Variables and functions */
 int ENODEV ; 
 int ether1_ramtest (struct net_device*,int) ; 

__attribute__((used)) static int
ether1_init_2(struct net_device *dev)
{
	int i;
	dev->mem_start = 0;

	i = ether1_ramtest (dev, 0x5a);

	if (i > 0)
		i = ether1_ramtest (dev, 0x1e);

	if (i <= 0)
	    	return -ENODEV;

	dev->mem_end = i;
	return 0;
}