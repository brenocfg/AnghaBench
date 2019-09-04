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
typedef  size_t u8 ;
typedef  size_t u16 ;

/* Variables and functions */
 long DIV_ROUND_CLOSEST (size_t,int) ; 

__attribute__((used)) static inline long in_from_reg(u8 reg, u8 nr, const u16 *scale_in)
{
	return DIV_ROUND_CLOSEST(reg * scale_in[nr], 100);
}