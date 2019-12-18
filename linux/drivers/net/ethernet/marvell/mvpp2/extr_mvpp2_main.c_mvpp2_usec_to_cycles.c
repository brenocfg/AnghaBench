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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ U32_MAX ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mvpp2_usec_to_cycles(u32 usec, unsigned long clk_hz)
{
	u64 tmp = (u64)clk_hz * usec;

	do_div(tmp, USEC_PER_SEC);

	return tmp > U32_MAX ? U32_MAX : tmp;
}