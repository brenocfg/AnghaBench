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

/* Variables and functions */
 scalar_t__ GPC_PGC_CPU_PDN ; 
 scalar_t__ gpc_base ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void imx_gpc_set_arm_power_in_lpm(bool power_off)
{
	writel_relaxed(power_off, gpc_base + GPC_PGC_CPU_PDN);
}