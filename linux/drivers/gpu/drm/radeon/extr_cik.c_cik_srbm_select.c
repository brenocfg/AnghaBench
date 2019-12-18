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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int MEID (int) ; 
 int PIPEID (int) ; 
 int QUEUEID (int) ; 
 int /*<<< orphan*/  SRBM_GFX_CNTL ; 
 int VMID (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cik_srbm_select(struct radeon_device *rdev,
			    u32 me, u32 pipe, u32 queue, u32 vmid)
{
	u32 srbm_gfx_cntl = (PIPEID(pipe & 0x3) |
			     MEID(me & 0x3) |
			     VMID(vmid & 0xf) |
			     QUEUEID(queue & 0x7));
	WREG32(SRBM_GFX_CNTL, srbm_gfx_cntl);
}