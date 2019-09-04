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
struct vfe_device {scalar_t__ base; int /*<<< orphan*/  reg_update; } ;
typedef  enum vfe_line_id { ____Placeholder_vfe_line_id } vfe_line_id ;

/* Variables and functions */
 scalar_t__ VFE_0_REG_UPDATE ; 
 int /*<<< orphan*/  VFE_0_REG_UPDATE_line_n (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vfe_reg_update(struct vfe_device *vfe, enum vfe_line_id line_id)
{
	vfe->reg_update |= VFE_0_REG_UPDATE_line_n(line_id);
	wmb();
	writel_relaxed(vfe->reg_update, vfe->base + VFE_0_REG_UPDATE);
	wmb();
}