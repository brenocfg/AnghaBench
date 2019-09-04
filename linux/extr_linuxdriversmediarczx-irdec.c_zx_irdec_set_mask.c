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
struct zx_irdec {scalar_t__ base; } ;

/* Variables and functions */
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void zx_irdec_set_mask(struct zx_irdec *irdec, unsigned int reg,
			      u32 mask, u32 value)
{
	u32 data;

	data = readl(irdec->base + reg);
	data &= ~mask;
	data |= value & mask;
	writel(data, irdec->base + reg);
}