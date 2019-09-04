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
struct xiic_i2c {scalar_t__ endianness; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LITTLE ; 
 int ioread32 (scalar_t__) ; 
 int ioread32be (scalar_t__) ; 

__attribute__((used)) static inline int xiic_getreg32(struct xiic_i2c *i2c, int reg)
{
	u32 ret;

	if (i2c->endianness == LITTLE)
		ret = ioread32(i2c->base + reg);
	else
		ret = ioread32be(i2c->base + reg);
	return ret;
}