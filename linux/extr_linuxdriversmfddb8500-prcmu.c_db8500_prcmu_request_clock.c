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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PRCMU_DSI0CLK ; 
 scalar_t__ PRCMU_DSI0ESCCLK ; 
 scalar_t__ PRCMU_DSI1CLK ; 
 scalar_t__ PRCMU_DSI2ESCCLK ; 
 scalar_t__ PRCMU_NUM_REG_CLOCKS ; 
 scalar_t__ PRCMU_PLLDSI ; 
 scalar_t__ PRCMU_PLLSOC0 ; 
 scalar_t__ PRCMU_PLLSOC1 ; 
 scalar_t__ PRCMU_SGACLK ; 
 scalar_t__ PRCMU_SYSCLK ; 
 scalar_t__ PRCMU_TIMCLK ; 
 int request_clock (scalar_t__,int) ; 
 int request_dsiclk (scalar_t__,int) ; 
 int request_dsiescclk (scalar_t__,int) ; 
 int request_pll (scalar_t__,int) ; 
 int request_plldsi (int) ; 
 int request_sga_clock (scalar_t__,int) ; 
 int request_sysclk (int) ; 
 int request_timclk (int) ; 

int db8500_prcmu_request_clock(u8 clock, bool enable)
{
	if (clock == PRCMU_SGACLK)
		return request_sga_clock(clock, enable);
	else if (clock < PRCMU_NUM_REG_CLOCKS)
		return request_clock(clock, enable);
	else if (clock == PRCMU_TIMCLK)
		return request_timclk(enable);
	else if ((clock == PRCMU_DSI0CLK) || (clock == PRCMU_DSI1CLK))
		return request_dsiclk((clock - PRCMU_DSI0CLK), enable);
	else if ((PRCMU_DSI0ESCCLK <= clock) && (clock <= PRCMU_DSI2ESCCLK))
		return request_dsiescclk((clock - PRCMU_DSI0ESCCLK), enable);
	else if (clock == PRCMU_PLLDSI)
		return request_plldsi(enable);
	else if (clock == PRCMU_SYSCLK)
		return request_sysclk(enable);
	else if ((clock == PRCMU_PLLSOC0) || (clock == PRCMU_PLLSOC1))
		return request_pll(clock, enable);
	else
		return -EINVAL;
}