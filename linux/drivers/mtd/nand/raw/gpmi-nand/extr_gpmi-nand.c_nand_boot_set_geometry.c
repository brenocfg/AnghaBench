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
struct boot_rom_geometry {int stride_size_in_pages; int search_area_stride_exponent; } ;
struct gpmi_nand_data {struct boot_rom_geometry rom_geometry; } ;

/* Variables and functions */

__attribute__((used)) static int nand_boot_set_geometry(struct gpmi_nand_data *this)
{
	struct boot_rom_geometry *geometry = &this->rom_geometry;

	/*
	 * Set the boot block stride size.
	 *
	 * In principle, we should be reading this from the OTP bits, since
	 * that's where the ROM is going to get it. In fact, we don't have any
	 * way to read the OTP bits, so we go with the default and hope for the
	 * best.
	 */
	geometry->stride_size_in_pages = 64;

	/*
	 * Set the search area stride exponent.
	 *
	 * In principle, we should be reading this from the OTP bits, since
	 * that's where the ROM is going to get it. In fact, we don't have any
	 * way to read the OTP bits, so we go with the default and hope for the
	 * best.
	 */
	geometry->search_area_stride_exponent = 2;
	return 0;
}