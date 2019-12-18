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

/* Variables and functions */

__attribute__((used)) static inline int FAN_FROM_REG(int reg, int tpc)
{
	if (tpc)
		return tpc * reg;
	else
		return (reg == 0 || reg == 0xffff) ? 0 : 90000 * 60 / reg;
}