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
typedef  int u32 ;
struct nvkm_falcon {scalar_t__ debug; } ;
struct hsf_fw_header {int patch_loc; int patch_sig; int sig_dbg_offset; int sig_dbg_size; int sig_prod_offset; int sig_prod_size; } ;
struct fw_bin_header {int header_offset; int data_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static void
hs_ucode_patch_signature(const struct nvkm_falcon *falcon, void *acr_image,
			 bool new_format)
{
	struct fw_bin_header *hsbin_hdr = acr_image;
	struct hsf_fw_header *fw_hdr = acr_image + hsbin_hdr->header_offset;
	void *hs_data = acr_image + hsbin_hdr->data_offset;
	void *sig;
	u32 sig_size;
	u32 patch_loc, patch_sig;

	/*
	 * I had the brilliant idea to "improve" the binary format by
	 * removing this useless indirection. However to make NVIDIA files
	 * directly compatible, let's support both format.
	 */
	if (new_format) {
		patch_loc = fw_hdr->patch_loc;
		patch_sig = fw_hdr->patch_sig;
	} else {
		patch_loc = *(u32 *)(acr_image + fw_hdr->patch_loc);
		patch_sig = *(u32 *)(acr_image + fw_hdr->patch_sig);
	}

	/* Falcon in debug or production mode? */
	if (falcon->debug) {
		sig = acr_image + fw_hdr->sig_dbg_offset;
		sig_size = fw_hdr->sig_dbg_size;
	} else {
		sig = acr_image + fw_hdr->sig_prod_offset;
		sig_size = fw_hdr->sig_prod_size;
	}

	/* Patch signature */
	memcpy(hs_data + patch_loc, sig + patch_sig, sig_size);
}