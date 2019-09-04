#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ baseaddr; } ;

/* Variables and functions */
 scalar_t__ A15_PWRDN_EN ; 
 scalar_t__ A7_PWRDN_EN ; 
 scalar_t__ MAX_CLUSTERS ; 
 scalar_t__ cluster_is_a15 (scalar_t__) ; 
 TYPE_1__* info ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void ve_spc_powerdown(u32 cluster, bool enable)
{
	u32 pwdrn_reg;

	if (cluster >= MAX_CLUSTERS)
		return;

	pwdrn_reg = cluster_is_a15(cluster) ? A15_PWRDN_EN : A7_PWRDN_EN;
	writel_relaxed(enable, info->baseaddr + pwdrn_reg);
}