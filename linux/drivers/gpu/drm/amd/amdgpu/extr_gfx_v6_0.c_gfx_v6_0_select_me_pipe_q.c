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
 int /*<<< orphan*/  DRM_INFO (char*) ; 

__attribute__((used)) static void gfx_v6_0_select_me_pipe_q(struct amdgpu_device *adev,
				  u32 me, u32 pipe, u32 q, u32 vm)
{
	DRM_INFO("Not implemented\n");
}