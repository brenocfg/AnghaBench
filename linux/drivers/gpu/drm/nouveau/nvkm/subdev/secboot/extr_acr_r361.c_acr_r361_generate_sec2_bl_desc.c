#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_sec2 {TYPE_4__* falcon; } ;
struct nvkm_acr {TYPE_2__* subdev; } ;
struct ls_ucode_img_desc {int /*<<< orphan*/  app_resident_data_size; int /*<<< orphan*/  app_imem_entry; int /*<<< orphan*/  app_resident_code_size; int /*<<< orphan*/  app_size; scalar_t__ app_resident_data_offset; scalar_t__ app_start_offset; } ;
struct ls_ucode_img {scalar_t__ ucode_off; struct ls_ucode_img_desc ucode_desc; } ;
struct acr_r361_pmu_bl_desc {int argc; int argv; void* overlay_dma_base; int /*<<< orphan*/  data_size; void* data_dma_base; int /*<<< orphan*/  code_entry_point; int /*<<< orphan*/  code_size_to_load; int /*<<< orphan*/  total_code_size; void* code_dma_base; int /*<<< orphan*/  dma_idx; } ;
struct TYPE_7__ {int /*<<< orphan*/  limit; } ;
struct TYPE_8__ {TYPE_3__ data; } ;
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_5__ {struct nvkm_sec2* sec2; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALCON_SEC2_DMAIDX_UCODE ; 
 scalar_t__ NVKM_MSGQUEUE_CMDLINE_SIZE ; 
 void* u64_to_flcn64 (scalar_t__) ; 

__attribute__((used)) static void
acr_r361_generate_sec2_bl_desc(const struct nvkm_acr *acr,
			       const struct ls_ucode_img *img, u64 wpr_addr,
			       void *_desc)
{
	const struct ls_ucode_img_desc *pdesc = &img->ucode_desc;
	const struct nvkm_sec2 *sec = acr->subdev->device->sec2;
	struct acr_r361_pmu_bl_desc *desc = _desc;
	u64 base, addr_code, addr_data;
	u32 addr_args;

	base = wpr_addr + img->ucode_off + pdesc->app_start_offset;
	/* For some reason we should not add app_resident_code_offset here */
	addr_code = base;
	addr_data = base + pdesc->app_resident_data_offset;
	addr_args = sec->falcon->data.limit;
	addr_args -= NVKM_MSGQUEUE_CMDLINE_SIZE;

	desc->dma_idx = FALCON_SEC2_DMAIDX_UCODE;
	desc->code_dma_base = u64_to_flcn64(addr_code);
	desc->total_code_size = pdesc->app_size;
	desc->code_size_to_load = pdesc->app_resident_code_size;
	desc->code_entry_point = pdesc->app_imem_entry;
	desc->data_dma_base = u64_to_flcn64(addr_data);
	desc->data_size = pdesc->app_resident_data_size;
	desc->overlay_dma_base = u64_to_flcn64(addr_code);
	desc->argc = 1;
	/* args are stored at the beginning of EMEM */
	desc->argv = 0x01000000;
}