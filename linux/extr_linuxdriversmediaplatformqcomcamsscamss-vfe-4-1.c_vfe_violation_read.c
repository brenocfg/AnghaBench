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
 scalar_t__ VFE_0_VIOLATION_STATUS ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void vfe_violation_read(struct vfe_device *vfe)
{
	u32 violation = readl_relaxed(vfe->base + VFE_0_VIOLATION_STATUS);

	pr_err_ratelimited("VFE: violation = 0x%08x\n", violation);
}