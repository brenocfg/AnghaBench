#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_15__ {size_t ucode_array_offset_bytes; size_t ucode_size_bytes; } ;
struct gfx_firmware_header_v1_0 {TYPE_5__ header; } ;
struct TYPE_16__ {TYPE_8__* mec_fw_obj; int /*<<< orphan*/  mec_fw_gpu_addr; TYPE_8__* hpd_eop_obj; int /*<<< orphan*/  hpd_eop_gpu_addr; int /*<<< orphan*/  queue_bitmap; } ;
struct TYPE_17__ {size_t num_compute_rings; TYPE_6__ mec; TYPE_4__* mec_fw; } ;
struct TYPE_13__ {scalar_t__ load_type; } ;
struct amdgpu_device {TYPE_7__ gfx; int /*<<< orphan*/  dev; TYPE_3__ firmware; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_11__ {int /*<<< orphan*/  size; } ;
struct TYPE_12__ {TYPE_1__ mem; } ;
struct TYPE_18__ {TYPE_2__ tbo; } ;
struct TYPE_14__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_DIRECT ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  AMDGPU_MAX_COMPUTE_QUEUES ; 
 size_t GFX10_MEC_HPD_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_reserved (struct amdgpu_device*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__**,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (TYPE_8__*) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (TYPE_8__*) ; 
 int /*<<< orphan*/  amdgpu_gfx_compute_queue_acquire (struct amdgpu_device*) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gfx_v10_0_mec_fini (struct amdgpu_device*) ; 
 unsigned int le32_to_cpu (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfx_v10_0_mec_init(struct amdgpu_device *adev)
{
	int r;
	u32 *hpd;
	const __le32 *fw_data = NULL;
	unsigned fw_size;
	u32 *fw = NULL;
	size_t mec_hpd_size;

	const struct gfx_firmware_header_v1_0 *mec_hdr = NULL;

	bitmap_zero(adev->gfx.mec.queue_bitmap, AMDGPU_MAX_COMPUTE_QUEUES);

	/* take ownership of the relevant compute queues */
	amdgpu_gfx_compute_queue_acquire(adev);
	mec_hpd_size = adev->gfx.num_compute_rings * GFX10_MEC_HPD_SIZE;

	r = amdgpu_bo_create_reserved(adev, mec_hpd_size, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_GTT,
				      &adev->gfx.mec.hpd_eop_obj,
				      &adev->gfx.mec.hpd_eop_gpu_addr,
				      (void **)&hpd);
	if (r) {
		dev_warn(adev->dev, "(%d) create HDP EOP bo failed\n", r);
		gfx_v10_0_mec_fini(adev);
		return r;
	}

	memset(hpd, 0, adev->gfx.mec.hpd_eop_obj->tbo.mem.size);

	amdgpu_bo_kunmap(adev->gfx.mec.hpd_eop_obj);
	amdgpu_bo_unreserve(adev->gfx.mec.hpd_eop_obj);

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_DIRECT) {
		mec_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.mec_fw->data;

		fw_data = (const __le32 *) (adev->gfx.mec_fw->data +
			 le32_to_cpu(mec_hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(mec_hdr->header.ucode_size_bytes);

		r = amdgpu_bo_create_reserved(adev, mec_hdr->header.ucode_size_bytes,
					      PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
					      &adev->gfx.mec.mec_fw_obj,
					      &adev->gfx.mec.mec_fw_gpu_addr,
					      (void **)&fw);
		if (r) {
			dev_err(adev->dev, "(%d) failed to create mec fw bo\n", r);
			gfx_v10_0_mec_fini(adev);
			return r;
		}

		memcpy(fw, fw_data, fw_size);

		amdgpu_bo_kunmap(adev->gfx.mec.mec_fw_obj);
		amdgpu_bo_unreserve(adev->gfx.mec.mec_fw_obj);
	}

	return 0;
}