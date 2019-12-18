#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ offset; } ;
typedef  size_t FIRMWARE_ID ;

/* Variables and functions */
 size_t FIRMWARE_ID_MAX ; 
 size_t FIRMWARE_ID_RLC_G_UCODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int gfx_v10_0_parse_rlc_toc (struct amdgpu_device*) ; 
 TYPE_1__* rlc_autoload_info ; 

__attribute__((used)) static uint32_t gfx_v10_0_calc_toc_total_size(struct amdgpu_device *adev)
{
	uint32_t total_size = 0;
	FIRMWARE_ID id;
	int ret;

	ret = gfx_v10_0_parse_rlc_toc(adev);
	if (ret) {
		dev_err(adev->dev, "failed to parse rlc toc\n");
		return 0;
	}

	for (id = FIRMWARE_ID_RLC_G_UCODE; id < FIRMWARE_ID_MAX; id++)
		total_size += rlc_autoload_info[id].size;

	/* In case the offset in rlc toc ucode is aligned */
	if (total_size < rlc_autoload_info[FIRMWARE_ID_MAX-1].offset)
		total_size = rlc_autoload_info[FIRMWARE_ID_MAX-1].offset +
				rlc_autoload_info[FIRMWARE_ID_MAX-1].size;

	return total_size;
}