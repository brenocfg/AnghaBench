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
 scalar_t__ VFE_0_GLOBAL_RESET_CMD ; 
 int VFE_0_GLOBAL_RESET_CMD_BUS ; 
 int VFE_0_GLOBAL_RESET_CMD_BUS_BDG ; 
 int VFE_0_GLOBAL_RESET_CMD_BUS_MISR ; 
 int VFE_0_GLOBAL_RESET_CMD_CAMIF ; 
 int VFE_0_GLOBAL_RESET_CMD_CORE ; 
 int VFE_0_GLOBAL_RESET_CMD_PM ; 
 int VFE_0_GLOBAL_RESET_CMD_REGISTER ; 
 int VFE_0_GLOBAL_RESET_CMD_TESTGEN ; 
 int VFE_0_GLOBAL_RESET_CMD_TIMER ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void vfe_global_reset(struct vfe_device *vfe)
{
	u32 reset_bits = VFE_0_GLOBAL_RESET_CMD_TESTGEN		|
			 VFE_0_GLOBAL_RESET_CMD_BUS_MISR	|
			 VFE_0_GLOBAL_RESET_CMD_PM		|
			 VFE_0_GLOBAL_RESET_CMD_TIMER		|
			 VFE_0_GLOBAL_RESET_CMD_REGISTER	|
			 VFE_0_GLOBAL_RESET_CMD_BUS_BDG		|
			 VFE_0_GLOBAL_RESET_CMD_BUS		|
			 VFE_0_GLOBAL_RESET_CMD_CAMIF		|
			 VFE_0_GLOBAL_RESET_CMD_CORE;

	writel_relaxed(reset_bits, vfe->base + VFE_0_GLOBAL_RESET_CMD);
}