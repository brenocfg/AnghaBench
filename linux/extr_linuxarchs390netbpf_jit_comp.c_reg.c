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
typedef  size_t u32 ;

/* Variables and functions */
 int* reg2hex ; 

__attribute__((used)) static inline u32 reg(u32 dst_reg, u32 src_reg)
{
	return reg2hex[dst_reg] << 4 | reg2hex[src_reg];
}