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
typedef  int /*<<< orphan*/  u32 ;
struct bfi_ioc_image_hdr {int dummy; } ;
struct bfa_ioc {int dummy; } ;
typedef  enum bfi_ioc_img_ver_cmp { ____Placeholder_bfi_ioc_img_ver_cmp } bfi_ioc_img_ver_cmp ;
typedef  enum bfa_status { ____Placeholder_bfa_status } bfa_status ;

/* Variables and functions */
 int BFA_STATUS_OK ; 
 int BFI_FLASH_CHUNK_SZ_WORDS ; 
 int BFI_IOC_IMG_VER_INCOMP ; 
 scalar_t__ bfa_ioc_flash_fwver_valid (struct bfi_ioc_image_hdr*) ; 
 int bfa_ioc_fw_ver_patch_cmp (struct bfi_ioc_image_hdr*,struct bfi_ioc_image_hdr*) ; 
 int bfa_nw_ioc_flash_img_get_chnk (struct bfa_ioc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum bfi_ioc_img_ver_cmp
bfa_ioc_flash_fwver_cmp(struct bfa_ioc *ioc,
			struct bfi_ioc_image_hdr *base_fwhdr)
{
	struct bfi_ioc_image_hdr *flash_fwhdr;
	enum bfa_status status;
	u32 fwimg[BFI_FLASH_CHUNK_SZ_WORDS];

	status = bfa_nw_ioc_flash_img_get_chnk(ioc, 0, fwimg);
	if (status != BFA_STATUS_OK)
		return BFI_IOC_IMG_VER_INCOMP;

	flash_fwhdr = (struct bfi_ioc_image_hdr *)fwimg;
	if (bfa_ioc_flash_fwver_valid(flash_fwhdr))
		return bfa_ioc_fw_ver_patch_cmp(base_fwhdr, flash_fwhdr);
	else
		return BFI_IOC_IMG_VER_INCOMP;
}