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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pci_bar_kva; } ;
struct bfa_ioc {TYPE_1__ pcidev; } ;
typedef  enum bfa_status { ____Placeholder_bfa_status } bfa_status ;

/* Variables and functions */
 scalar_t__ BFA_FLASH_PART_FWIMG_ADDR ; 
 int /*<<< orphan*/  BFI_FLASH_CHUNK_SZ ; 
 int bfa_flash_raw_read (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bfa_status
bfa_nw_ioc_flash_img_get_chnk(struct bfa_ioc *ioc, u32 off,
			      u32 *fwimg)
{
	return bfa_flash_raw_read(ioc->pcidev.pci_bar_kva,
			BFA_FLASH_PART_FWIMG_ADDR + (off * sizeof(u32)),
			(char *)fwimg, BFI_FLASH_CHUNK_SZ);
}