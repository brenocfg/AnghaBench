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
typedef  int u64 ;
struct nvkm_secboot {scalar_t__ wpr_size; } ;
struct nvkm_gpuobj {int addr; int size; } ;
struct TYPE_6__ {int no_regions; TYPE_2__* region_props; } ;
struct acr_r367_hsflcn_desc {int wpr_region_id; int ucode_blob_base; int ucode_blob_size; TYPE_3__ regions; } ;
struct acr_r352 {TYPE_1__* func; struct nvkm_gpuobj* ls_blob; } ;
struct TYPE_5__ {int start_addr; int end_addr; int region_id; int read_mask; int write_mask; int client_mask; int shadow_mem_start_addr; } ;
struct TYPE_4__ {scalar_t__ shadow_blob; } ;

/* Variables and functions */

void
acr_r367_fixup_hs_desc(struct acr_r352 *acr, struct nvkm_secboot *sb,
		       void *_desc)
{
	struct acr_r367_hsflcn_desc *desc = _desc;
	struct nvkm_gpuobj *ls_blob = acr->ls_blob;

	/* WPR region information if WPR is not fixed */
	if (sb->wpr_size == 0) {
		u64 wpr_start = ls_blob->addr;
		u64 wpr_end = ls_blob->addr + ls_blob->size;

		if (acr->func->shadow_blob)
			wpr_start += ls_blob->size / 2;

		desc->wpr_region_id = 1;
		desc->regions.no_regions = 2;
		desc->regions.region_props[0].start_addr = wpr_start >> 8;
		desc->regions.region_props[0].end_addr = wpr_end >> 8;
		desc->regions.region_props[0].region_id = 1;
		desc->regions.region_props[0].read_mask = 0xf;
		desc->regions.region_props[0].write_mask = 0xc;
		desc->regions.region_props[0].client_mask = 0x2;
		if (acr->func->shadow_blob)
			desc->regions.region_props[0].shadow_mem_start_addr =
							     ls_blob->addr >> 8;
		else
			desc->regions.region_props[0].shadow_mem_start_addr = 0;
	} else {
		desc->ucode_blob_base = ls_blob->addr;
		desc->ucode_blob_size = ls_blob->size;
	}
}