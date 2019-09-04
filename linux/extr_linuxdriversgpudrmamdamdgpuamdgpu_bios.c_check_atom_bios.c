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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IS_VALID_VBIOS (int*) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
 int /*<<< orphan*/  memcmp (int*,char*,int) ; 

__attribute__((used)) static bool check_atom_bios(uint8_t *bios, size_t size)
{
	uint16_t tmp, bios_header_start;

	if (!bios || size < 0x49) {
		DRM_INFO("vbios mem is null or mem size is wrong\n");
		return false;
	}

	if (!AMD_IS_VALID_VBIOS(bios)) {
		DRM_INFO("BIOS signature incorrect %x %x\n", bios[0], bios[1]);
		return false;
	}

	bios_header_start = bios[0x48] | (bios[0x49] << 8);
	if (!bios_header_start) {
		DRM_INFO("Can't locate bios header\n");
		return false;
	}

	tmp = bios_header_start + 4;
	if (size < tmp) {
		DRM_INFO("BIOS header is broken\n");
		return false;
	}

	if (!memcmp(bios + tmp, "ATOM", 4) ||
	    !memcmp(bios + tmp, "MOTA", 4)) {
		DRM_DEBUG("ATOMBIOS detected\n");
		return true;
	}

	return false;
}