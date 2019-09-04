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
struct jz4780_i2c {scalar_t__ iomem; } ;

/* Variables and functions */
 unsigned short readw (scalar_t__) ; 

__attribute__((used)) static inline unsigned short jz4780_i2c_readw(struct jz4780_i2c *i2c,
					      unsigned long offset)
{
	return readw(i2c->iomem + offset);
}