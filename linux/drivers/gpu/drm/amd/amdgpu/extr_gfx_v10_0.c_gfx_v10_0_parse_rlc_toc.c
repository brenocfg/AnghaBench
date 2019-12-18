#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ rlc_toc_buf; int /*<<< orphan*/  rlc_toc_gpu_addr; int /*<<< orphan*/  rlc_toc_bo; } ;
struct TYPE_8__ {TYPE_2__ rlc; } ;
struct TYPE_6__ {int /*<<< orphan*/  toc_bin_size; int /*<<< orphan*/  toc_start_addr; } ;
struct amdgpu_device {TYPE_3__ gfx; TYPE_1__ psp; int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {size_t id; int offset; int size; } ;
struct TYPE_9__ {size_t id; int offset; int size; } ;
typedef  TYPE_4__ RLC_TABLE_OF_CONTENT ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GTT ; 
 size_t FIRMWARE_ID_CP_CE ; 
 size_t FIRMWARE_ID_CP_MES ; 
 size_t FIRMWARE_ID_INVALID ; 
 size_t FIRMWARE_ID_MAX ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_reserved (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* rlc_autoload_info ; 

__attribute__((used)) static int gfx_v10_0_parse_rlc_toc(struct amdgpu_device *adev)
{
	int ret;
	RLC_TABLE_OF_CONTENT *rlc_toc;

	ret = amdgpu_bo_create_reserved(adev, adev->psp.toc_bin_size, PAGE_SIZE,
					AMDGPU_GEM_DOMAIN_GTT,
					&adev->gfx.rlc.rlc_toc_bo,
					&adev->gfx.rlc.rlc_toc_gpu_addr,
					(void **)&adev->gfx.rlc.rlc_toc_buf);
	if (ret) {
		dev_err(adev->dev, "(%d) failed to create rlc toc bo\n", ret);
		return ret;
	}

	/* Copy toc from psp sos fw to rlc toc buffer */
	memcpy(adev->gfx.rlc.rlc_toc_buf, adev->psp.toc_start_addr, adev->psp.toc_bin_size);

	rlc_toc = (RLC_TABLE_OF_CONTENT *)adev->gfx.rlc.rlc_toc_buf;
	while (rlc_toc && (rlc_toc->id > FIRMWARE_ID_INVALID) &&
		(rlc_toc->id < FIRMWARE_ID_MAX)) {
		if ((rlc_toc->id >= FIRMWARE_ID_CP_CE) &&
		    (rlc_toc->id <= FIRMWARE_ID_CP_MES)) {
			/* Offset needs 4KB alignment */
			rlc_toc->offset = ALIGN(rlc_toc->offset * 4, PAGE_SIZE);
		}

		rlc_autoload_info[rlc_toc->id].id = rlc_toc->id;
		rlc_autoload_info[rlc_toc->id].offset = rlc_toc->offset * 4;
		rlc_autoload_info[rlc_toc->id].size = rlc_toc->size * 4;

		rlc_toc++;
	};

	return 0;
}