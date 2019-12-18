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
typedef  int u8 ;

/* Variables and functions */
 int LM3533_REG_ALS_BOUNDARY_BASE ; 

__attribute__((used)) static inline u8 lm3533_als_get_threshold_reg(unsigned nr, bool raising)
{
	u8 offset = !raising;

	return LM3533_REG_ALS_BOUNDARY_BASE + 2 * nr + offset;
}