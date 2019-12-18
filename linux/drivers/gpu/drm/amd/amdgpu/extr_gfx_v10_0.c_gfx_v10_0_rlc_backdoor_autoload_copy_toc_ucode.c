#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {void* rlc_toc_buf; } ;
struct TYPE_5__ {TYPE_1__ rlc; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 size_t FIRMWARE_ID_RLC_TOC ; 
 int /*<<< orphan*/  gfx_v10_0_rlc_backdoor_autoload_copy_ucode (struct amdgpu_device*,size_t,void*,int /*<<< orphan*/ ) ; 
 TYPE_3__* rlc_autoload_info ; 

__attribute__((used)) static void gfx_v10_0_rlc_backdoor_autoload_copy_toc_ucode(struct amdgpu_device *adev)
{
	void *data;
	uint32_t size;

	data = adev->gfx.rlc.rlc_toc_buf;
	size = rlc_autoload_info[FIRMWARE_ID_RLC_TOC].size;

	gfx_v10_0_rlc_backdoor_autoload_copy_ucode(adev,
						   FIRMWARE_ID_RLC_TOC,
						   data, size);
}