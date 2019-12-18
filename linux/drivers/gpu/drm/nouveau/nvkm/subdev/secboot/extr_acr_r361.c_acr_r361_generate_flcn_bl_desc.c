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
typedef  scalar_t__ u64 ;
struct nvkm_acr {int dummy; } ;
struct ls_ucode_img_desc {int /*<<< orphan*/  app_resident_data_size; int /*<<< orphan*/  app_imem_entry; int /*<<< orphan*/  app_resident_code_size; scalar_t__ app_resident_code_offset; scalar_t__ app_resident_data_offset; scalar_t__ app_start_offset; } ;
struct ls_ucode_img {scalar_t__ ucode_off; struct ls_ucode_img_desc ucode_desc; } ;
struct acr_r361_flcn_bl_desc {int /*<<< orphan*/  data_size; void* data_dma_base; int /*<<< orphan*/  code_entry_point; int /*<<< orphan*/  non_sec_code_size; scalar_t__ non_sec_code_off; void* code_dma_base; int /*<<< orphan*/  ctx_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALCON_DMAIDX_UCODE ; 
 void* u64_to_flcn64 (scalar_t__) ; 

__attribute__((used)) static void
acr_r361_generate_flcn_bl_desc(const struct nvkm_acr *acr,
			       const struct ls_ucode_img *img, u64 wpr_addr,
			       void *_desc)
{
	struct acr_r361_flcn_bl_desc *desc = _desc;
	const struct ls_ucode_img_desc *pdesc = &img->ucode_desc;
	u64 base, addr_code, addr_data;

	base = wpr_addr + img->ucode_off + pdesc->app_start_offset;
	addr_code = base + pdesc->app_resident_code_offset;
	addr_data = base + pdesc->app_resident_data_offset;

	desc->ctx_dma = FALCON_DMAIDX_UCODE;
	desc->code_dma_base = u64_to_flcn64(addr_code);
	desc->non_sec_code_off = pdesc->app_resident_code_offset;
	desc->non_sec_code_size = pdesc->app_resident_code_size;
	desc->code_entry_point = pdesc->app_imem_entry;
	desc->data_dma_base = u64_to_flcn64(addr_data);
	desc->data_size = pdesc->app_resident_data_size;
}