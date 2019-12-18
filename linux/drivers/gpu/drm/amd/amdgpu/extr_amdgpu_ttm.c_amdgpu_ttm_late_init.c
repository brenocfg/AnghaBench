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
struct amdgpu_device {int /*<<< orphan*/  stolen_vga_memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

void amdgpu_ttm_late_init(struct amdgpu_device *adev)
{
	void *stolen_vga_buf;
	/* return the VGA stolen memory (if any) back to VRAM */
	amdgpu_bo_free_kernel(&adev->stolen_vga_memory, NULL, &stolen_vga_buf);
}