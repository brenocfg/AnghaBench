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
struct TYPE_2__ {scalar_t__ patch; scalar_t__ phase; scalar_t__ build; } ;
struct bfi_ioc_image_hdr {TYPE_1__ fwver; } ;
typedef  enum bfi_ioc_img_ver_cmp { ____Placeholder_bfi_ioc_img_ver_cmp } bfi_ioc_img_ver_cmp ;

/* Variables and functions */
 int BFI_IOC_IMG_VER_BETTER ; 
 int BFI_IOC_IMG_VER_INCOMP ; 
 int BFI_IOC_IMG_VER_OLD ; 
 int BFI_IOC_IMG_VER_SAME ; 
 int /*<<< orphan*/  bfa_ioc_fw_ver_compatible (struct bfi_ioc_image_hdr*,struct bfi_ioc_image_hdr*) ; 
 scalar_t__ fwhdr_is_ga (struct bfi_ioc_image_hdr*) ; 

__attribute__((used)) static enum bfi_ioc_img_ver_cmp
bfa_ioc_fw_ver_patch_cmp(struct bfi_ioc_image_hdr *base_fwhdr,
			 struct bfi_ioc_image_hdr *fwhdr_to_cmp)
{
	if (!bfa_ioc_fw_ver_compatible(base_fwhdr, fwhdr_to_cmp))
		return BFI_IOC_IMG_VER_INCOMP;

	if (fwhdr_to_cmp->fwver.patch > base_fwhdr->fwver.patch)
		return BFI_IOC_IMG_VER_BETTER;
	else if (fwhdr_to_cmp->fwver.patch < base_fwhdr->fwver.patch)
		return BFI_IOC_IMG_VER_OLD;

	/* GA takes priority over internal builds of the same patch stream.
	 * At this point major minor maint and patch numbers are same.
	 */
	if (fwhdr_is_ga(base_fwhdr))
		if (fwhdr_is_ga(fwhdr_to_cmp))
			return BFI_IOC_IMG_VER_SAME;
		else
			return BFI_IOC_IMG_VER_OLD;
	else
		if (fwhdr_is_ga(fwhdr_to_cmp))
			return BFI_IOC_IMG_VER_BETTER;

	if (fwhdr_to_cmp->fwver.phase > base_fwhdr->fwver.phase)
		return BFI_IOC_IMG_VER_BETTER;
	else if (fwhdr_to_cmp->fwver.phase < base_fwhdr->fwver.phase)
		return BFI_IOC_IMG_VER_OLD;

	if (fwhdr_to_cmp->fwver.build > base_fwhdr->fwver.build)
		return BFI_IOC_IMG_VER_BETTER;
	else if (fwhdr_to_cmp->fwver.build < base_fwhdr->fwver.build)
		return BFI_IOC_IMG_VER_OLD;

	/* All Version Numbers are equal.
	 * Md5 check to be done as a part of compatibility check.
	 */
	return BFI_IOC_IMG_VER_SAME;
}