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
typedef  int u32 ;
struct dw_i2c_dev {int flags; scalar_t__ base; } ;

/* Variables and functions */
 int ACCESS_16BIT ; 
 int ACCESS_SWAP ; 
 int readl_relaxed (scalar_t__) ; 
 int readw_relaxed (scalar_t__) ; 
 int swab32 (int) ; 

u32 dw_readl(struct dw_i2c_dev *dev, int offset)
{
	u32 value;

	if (dev->flags & ACCESS_16BIT)
		value = readw_relaxed(dev->base + offset) |
			(readw_relaxed(dev->base + offset + 2) << 16);
	else
		value = readl_relaxed(dev->base + offset);

	if (dev->flags & ACCESS_SWAP)
		return swab32(value);
	else
		return value;
}