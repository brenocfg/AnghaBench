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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBIO ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmBIF_BX_PF0_GPU_HDP_FLUSH_REQ ; 

__attribute__((used)) static u32 nbio_v6_1_get_hdp_flush_req_offset(struct amdgpu_device *adev)
{
	return SOC15_REG_OFFSET(NBIO, 0, mmBIF_BX_PF0_GPU_HDP_FLUSH_REQ);
}