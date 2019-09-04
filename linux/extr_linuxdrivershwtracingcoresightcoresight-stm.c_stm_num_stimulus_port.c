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
typedef  int u32 ;
struct stm_drvdata {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CORESIGHT_DEVID ; 
 int STM_32_CHANNEL ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static u32 stm_num_stimulus_port(struct stm_drvdata *drvdata)
{
	u32 numsp;

	numsp = readl_relaxed(drvdata->base + CORESIGHT_DEVID);
	/*
	 * NUMPS in STMDEVID is 17 bit long and if equal to 0x0,
	 * 32 stimulus ports are supported.
	 */
	numsp &= 0x1ffff;
	if (!numsp)
		numsp = STM_32_CHANNEL;
	return numsp;
}