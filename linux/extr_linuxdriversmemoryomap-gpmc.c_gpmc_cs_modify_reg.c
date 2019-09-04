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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  gpmc_cs_read_reg (int,int) ; 
 int /*<<< orphan*/  gpmc_cs_write_reg (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gpmc_cs_modify_reg(int cs, int reg, u32 mask, bool value)
{
	u32 l;

	l = gpmc_cs_read_reg(cs, reg);
	if (value)
		l |= mask;
	else
		l &= ~mask;
	gpmc_cs_write_reg(cs, reg, l);
}