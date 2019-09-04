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
struct bfi_ioc_image_hdr {int dummy; } ;
struct bfa_ioc {int dummy; } ;
typedef  enum bfi_ioc_img_ver_cmp { ____Placeholder_bfi_ioc_img_ver_cmp } bfi_ioc_img_ver_cmp ;

/* Variables and functions */
 int BFI_IOC_IMG_VER_BETTER ; 
 int BFI_IOC_IMG_VER_INCOMP ; 
 int BFI_IOC_IMG_VER_OLD ; 
 int BFI_IOC_IMG_VER_SAME ; 
 scalar_t__ bfa_cb_image_get_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_asic_gen (struct bfa_ioc*) ; 
 int bfa_ioc_flash_fwver_cmp (struct bfa_ioc*,struct bfi_ioc_image_hdr*) ; 
 int bfa_ioc_fw_ver_patch_cmp (struct bfi_ioc_image_hdr*,struct bfi_ioc_image_hdr*) ; 

bool
bfa_nw_ioc_fwver_cmp(struct bfa_ioc *ioc, struct bfi_ioc_image_hdr *fwhdr)
{
	struct bfi_ioc_image_hdr *drv_fwhdr;
	enum bfi_ioc_img_ver_cmp smem_flash_cmp, drv_smem_cmp;

	drv_fwhdr = (struct bfi_ioc_image_hdr *)
		bfa_cb_image_get_chunk(bfa_ioc_asic_gen(ioc), 0);

	/* If smem is incompatible or old, driver should not work with it. */
	drv_smem_cmp = bfa_ioc_fw_ver_patch_cmp(drv_fwhdr, fwhdr);
	if (drv_smem_cmp == BFI_IOC_IMG_VER_INCOMP ||
	    drv_smem_cmp == BFI_IOC_IMG_VER_OLD) {
		return false;
	}

	/* IF Flash has a better F/W than smem do not work with smem.
	 * If smem f/w == flash f/w, as smem f/w not old | incmp, work with it.
	 * If Flash is old or incomp work with smem iff smem f/w == drv f/w.
	 */
	smem_flash_cmp = bfa_ioc_flash_fwver_cmp(ioc, fwhdr);

	if (smem_flash_cmp == BFI_IOC_IMG_VER_BETTER)
		return false;
	else if (smem_flash_cmp == BFI_IOC_IMG_VER_SAME)
		return true;
	else
		return (drv_smem_cmp == BFI_IOC_IMG_VER_SAME) ?
			true : false;
}