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
typedef  int u32 ;

/* Variables and functions */
 int A9WDOG_ID_MASK ; 
 int /*<<< orphan*/  MB4H_A9WDOG_LOAD ; 
 int prcmu_a9wdog (int /*<<< orphan*/ ,int,int,int,int) ; 

int db8500_prcmu_load_a9wdog(u8 id, u32 timeout)
{
	return prcmu_a9wdog(MB4H_A9WDOG_LOAD,
			    (id & A9WDOG_ID_MASK) |
			    /*
			     * Put the lowest 28 bits of timeout at
			     * offset 4. Four first bits are used for id.
			     */
			    (u8)((timeout << 4) & 0xf0),
			    (u8)((timeout >> 4) & 0xff),
			    (u8)((timeout >> 12) & 0xff),
			    (u8)((timeout >> 20) & 0xff));
}