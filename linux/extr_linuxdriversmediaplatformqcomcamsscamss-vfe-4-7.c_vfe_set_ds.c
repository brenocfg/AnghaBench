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
typedef  int /*<<< orphan*/  u32 ;
struct vfe_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_0 ; 
 int /*<<< orphan*/  VFE_0_BUS_BDG_DS_CFG_0_CFG ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_1 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_10 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_11 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_12 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_13 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_14 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_15 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_16 ; 
 int /*<<< orphan*/  VFE_0_BUS_BDG_DS_CFG_16_CFG ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_2 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_3 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_4 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_5 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_6 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_7 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_8 ; 
 scalar_t__ VFE_0_BUS_BDG_DS_CFG_9 ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vfe_set_ds(struct vfe_device *vfe)
{
	u32 val = VFE_0_BUS_BDG_DS_CFG_0_CFG;
	u32 val16 = VFE_0_BUS_BDG_DS_CFG_16_CFG;

	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_0);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_1);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_2);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_3);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_4);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_5);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_6);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_7);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_8);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_9);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_10);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_11);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_12);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_13);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_14);
	writel_relaxed(val, vfe->base + VFE_0_BUS_BDG_DS_CFG_15);
	writel_relaxed(val16, vfe->base + VFE_0_BUS_BDG_DS_CFG_16);
}