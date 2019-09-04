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
struct vfe_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ VFE_0_CLAMP_ENC_MAX_CFG ; 
 int VFE_0_CLAMP_ENC_MAX_CFG_CH0 ; 
 int VFE_0_CLAMP_ENC_MAX_CFG_CH1 ; 
 int VFE_0_CLAMP_ENC_MAX_CFG_CH2 ; 
 scalar_t__ VFE_0_CLAMP_ENC_MIN_CFG ; 
 int VFE_0_CLAMP_ENC_MIN_CFG_CH0 ; 
 int VFE_0_CLAMP_ENC_MIN_CFG_CH1 ; 
 int VFE_0_CLAMP_ENC_MIN_CFG_CH2 ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void vfe_set_clamp_cfg(struct vfe_device *vfe)
{
	u32 val = VFE_0_CLAMP_ENC_MAX_CFG_CH0 |
		VFE_0_CLAMP_ENC_MAX_CFG_CH1 |
		VFE_0_CLAMP_ENC_MAX_CFG_CH2;

	writel_relaxed(val, vfe->base + VFE_0_CLAMP_ENC_MAX_CFG);

	val = VFE_0_CLAMP_ENC_MIN_CFG_CH0 |
		VFE_0_CLAMP_ENC_MIN_CFG_CH1 |
		VFE_0_CLAMP_ENC_MIN_CFG_CH2;

	writel_relaxed(val, vfe->base + VFE_0_CLAMP_ENC_MIN_CFG);
}