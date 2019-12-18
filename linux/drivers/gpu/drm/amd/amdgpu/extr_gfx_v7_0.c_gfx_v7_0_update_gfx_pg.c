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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfx_v7_0_enable_gfx_cgpg (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_enable_gfx_dynamic_mgpg (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_enable_gfx_static_mgpg (struct amdgpu_device*,int) ; 

__attribute__((used)) static void gfx_v7_0_update_gfx_pg(struct amdgpu_device *adev, bool enable)
{
	gfx_v7_0_enable_gfx_cgpg(adev, enable);
	gfx_v7_0_enable_gfx_static_mgpg(adev, enable);
	gfx_v7_0_enable_gfx_dynamic_mgpg(adev, enable);
}