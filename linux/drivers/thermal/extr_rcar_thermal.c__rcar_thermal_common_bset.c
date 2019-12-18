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
struct rcar_thermal_common {int base; } ;

/* Variables and functions */
 int ioread32 (int) ; 
 int /*<<< orphan*/  iowrite32 (int,int) ; 

__attribute__((used)) static void _rcar_thermal_common_bset(struct rcar_thermal_common *common,
				      u32 reg, u32 mask, u32 data)
{
	u32 val;

	val = ioread32(common->base + reg);
	val &= ~mask;
	val |= (data & mask);
	iowrite32(val, common->base + reg);
}