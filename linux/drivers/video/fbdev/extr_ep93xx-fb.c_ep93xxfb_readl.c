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
struct ep93xx_fbi {scalar_t__ mmio_base; } ;

/* Variables and functions */
 unsigned int __raw_readl (scalar_t__) ; 

__attribute__((used)) static inline unsigned int ep93xxfb_readl(struct ep93xx_fbi *fbi,
					  unsigned int off)
{
	return __raw_readl(fbi->mmio_base + off);
}