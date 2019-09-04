#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct nvkm_secboot {scalar_t__ wpr_size; } ;
struct nvkm_gpuobj {int addr; int size; } ;
struct TYPE_4__ {int no_regions; TYPE_1__* region_props; } ;
struct hsflcn_acr_desc {int wpr_region_id; int ucode_blob_base; int ucode_blob_size; TYPE_2__ regions; } ;
struct acr_r352 {struct nvkm_gpuobj* ls_blob; } ;
struct TYPE_3__ {int start_addr; int end_addr; int region_id; int read_mask; int write_mask; int client_mask; } ;

/* Variables and functions */

void
acr_r352_fixup_hs_desc(struct acr_r352 *acr, struct nvkm_secboot *sb,
		       void *_desc)
{
	struct hsflcn_acr_desc *desc = _desc;
	struct nvkm_gpuobj *ls_blob = acr->ls_blob;

	/* WPR region information if WPR is not fixed */
	if (sb->wpr_size == 0) {
		u64 wpr_start = ls_blob->addr;
		u64 wpr_end = wpr_start + ls_blob->size;

		desc->wpr_region_id = 1;
		desc->regions.no_regions = 2;
		desc->regions.region_props[0].start_addr = wpr_start >> 8;
		desc->regions.region_props[0].end_addr = wpr_end >> 8;
		desc->regions.region_props[0].region_id = 1;
		desc->regions.region_props[0].read_mask = 0xf;
		desc->regions.region_props[0].write_mask = 0xc;
		desc->regions.region_props[0].client_mask = 0x2;
	} else {
		desc->ucode_blob_base = ls_blob->addr;
		desc->ucode_blob_size = ls_blob->size;
	}
}