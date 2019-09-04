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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  vpif_clr_bit (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vpif_set_bit (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void vpif_wr_bit(u32 reg, u32 bit, u32 val)
{
	if (val)
		vpif_set_bit(reg, bit);
	else
		vpif_clr_bit(reg, bit);
}