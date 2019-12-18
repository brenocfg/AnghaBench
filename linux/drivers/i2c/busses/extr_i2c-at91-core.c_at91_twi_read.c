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
struct at91_twi_dev {unsigned int base; } ;

/* Variables and functions */
 int readl_relaxed (unsigned int) ; 

unsigned at91_twi_read(struct at91_twi_dev *dev, unsigned reg)
{
	return readl_relaxed(dev->base + reg);
}