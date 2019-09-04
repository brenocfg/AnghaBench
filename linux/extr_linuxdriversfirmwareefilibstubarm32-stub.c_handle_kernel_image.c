#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
struct TYPE_3__ {unsigned long image_size; } ;
typedef  TYPE_1__ efi_loaded_image_t ;

/* Variables and functions */
 scalar_t__ EFI_LOAD_ERROR ; 
 scalar_t__ EFI_SUCCESS ; 
 scalar_t__ MAX_UNCOMP_KERNEL_SIZE ; 
 int /*<<< orphan*/  SZ_128M ; 
 unsigned long ZIMAGE_OFFSET_LIMIT ; 
 int /*<<< orphan*/  efi_free (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 scalar_t__ efi_relocate_kernel (int /*<<< orphan*/ *,unsigned long*,unsigned long,unsigned long,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_efi_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ reserve_kernel_base (int /*<<< orphan*/ *,unsigned long,unsigned long*,unsigned long*) ; 
 unsigned long round_up (unsigned long,int /*<<< orphan*/ ) ; 

efi_status_t handle_kernel_image(efi_system_table_t *sys_table,
				 unsigned long *image_addr,
				 unsigned long *image_size,
				 unsigned long *reserve_addr,
				 unsigned long *reserve_size,
				 unsigned long dram_base,
				 efi_loaded_image_t *image)
{
	efi_status_t status;

	/*
	 * Verify that the DRAM base address is compatible with the ARM
	 * boot protocol, which determines the base of DRAM by masking
	 * off the low 27 bits of the address at which the zImage is
	 * loaded. These assumptions are made by the decompressor,
	 * before any memory map is available.
	 */
	dram_base = round_up(dram_base, SZ_128M);

	status = reserve_kernel_base(sys_table, dram_base, reserve_addr,
				     reserve_size);
	if (status != EFI_SUCCESS) {
		pr_efi_err(sys_table, "Unable to allocate memory for uncompressed kernel.\n");
		return status;
	}

	/*
	 * Relocate the zImage, so that it appears in the lowest 128 MB
	 * memory window.
	 */
	*image_size = image->image_size;
	status = efi_relocate_kernel(sys_table, image_addr, *image_size,
				     *image_size,
				     dram_base + MAX_UNCOMP_KERNEL_SIZE, 0);
	if (status != EFI_SUCCESS) {
		pr_efi_err(sys_table, "Failed to relocate kernel.\n");
		efi_free(sys_table, *reserve_size, *reserve_addr);
		*reserve_size = 0;
		return status;
	}

	/*
	 * Check to see if we were able to allocate memory low enough
	 * in memory. The kernel determines the base of DRAM from the
	 * address at which the zImage is loaded.
	 */
	if (*image_addr + *image_size > dram_base + ZIMAGE_OFFSET_LIMIT) {
		pr_efi_err(sys_table, "Failed to relocate kernel, no low memory available.\n");
		efi_free(sys_table, *reserve_size, *reserve_addr);
		*reserve_size = 0;
		efi_free(sys_table, *image_size, *image_addr);
		*image_size = 0;
		return EFI_LOAD_ERROR;
	}
	return EFI_SUCCESS;
}