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
typedef  int uint16_t ;
struct radeon_device {int* bios; int bios_header_start; int is_atom_bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 void* RBIOS16 (int) ; 
 int RBIOS8 (int) ; 
 int igp_read_bios_from_vram (struct radeon_device*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int /*<<< orphan*/  memcmp (int*,char*,int) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 int radeon_acpi_vfct_bios (struct radeon_device*) ; 
 int radeon_atrm_get_bios (struct radeon_device*) ; 
 int radeon_read_bios (struct radeon_device*) ; 
 int radeon_read_disabled_bios (struct radeon_device*) ; 
 int radeon_read_platform_bios (struct radeon_device*) ; 

bool radeon_get_bios(struct radeon_device *rdev)
{
	bool r;
	uint16_t tmp;

	r = radeon_atrm_get_bios(rdev);
	if (r == false)
		r = radeon_acpi_vfct_bios(rdev);
	if (r == false)
		r = igp_read_bios_from_vram(rdev);
	if (r == false)
		r = radeon_read_bios(rdev);
	if (r == false)
		r = radeon_read_disabled_bios(rdev);
	if (r == false)
		r = radeon_read_platform_bios(rdev);
	if (r == false || rdev->bios == NULL) {
		DRM_ERROR("Unable to locate a BIOS ROM\n");
		rdev->bios = NULL;
		return false;
	}
	if (rdev->bios[0] != 0x55 || rdev->bios[1] != 0xaa) {
		printk("BIOS signature incorrect %x %x\n", rdev->bios[0], rdev->bios[1]);
		goto free_bios;
	}

	tmp = RBIOS16(0x18);
	if (RBIOS8(tmp + 0x14) != 0x0) {
		DRM_INFO("Not an x86 BIOS ROM, not using.\n");
		goto free_bios;
	}

	rdev->bios_header_start = RBIOS16(0x48);
	if (!rdev->bios_header_start) {
		goto free_bios;
	}
	tmp = rdev->bios_header_start + 4;
	if (!memcmp(rdev->bios + tmp, "ATOM", 4) ||
	    !memcmp(rdev->bios + tmp, "MOTA", 4)) {
		rdev->is_atom_bios = true;
	} else {
		rdev->is_atom_bios = false;
	}

	DRM_DEBUG("%sBIOS detected\n", rdev->is_atom_bios ? "ATOM" : "COM");
	return true;
free_bios:
	kfree(rdev->bios);
	rdev->bios = NULL;
	return false;
}