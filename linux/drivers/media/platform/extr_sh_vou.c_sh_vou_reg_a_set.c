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
struct sh_vou_device {scalar_t__ base; } ;

/* Variables and functions */
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 

__attribute__((used)) static void sh_vou_reg_a_set(struct sh_vou_device *vou_dev, unsigned int reg,
			     u32 value, u32 mask)
{
	u32 old = __raw_readl(vou_dev->base + reg);

	value = (value & mask) | (old & ~mask);
	__raw_writel(value, vou_dev->base + reg);
}