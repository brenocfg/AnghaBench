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
typedef  int uint32_t ;

/* Variables and functions */
 int QPU_W_ACC0 ; 
 int QPU_W_ACC3 ; 

__attribute__((used)) static uint32_t
waddr_to_live_reg_index(uint32_t waddr, bool is_b)
{
	if (waddr < 32) {
		if (is_b)
			return 32 + waddr;
		else
			return waddr;
	} else if (waddr <= QPU_W_ACC3) {
		return 64 + waddr - QPU_W_ACC0;
	} else {
		return ~0;
	}
}