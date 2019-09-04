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
 size_t CBE_PM_CTR_ENABLE ; 
 int /*<<< orphan*/  cbe_write_pm07_control (size_t,size_t,size_t) ; 

__attribute__((used)) static inline void enable_ctr(u32 cpu, u32 ctr, u32 *pm07_cntrl)
{

	pm07_cntrl[ctr] |= CBE_PM_CTR_ENABLE;
	cbe_write_pm07_control(cpu, ctr, pm07_cntrl[ctr]);
}