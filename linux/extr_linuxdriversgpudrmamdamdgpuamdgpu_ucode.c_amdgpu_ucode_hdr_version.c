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
struct TYPE_2__ {scalar_t__ header_version_major; scalar_t__ header_version_minor; } ;
union amdgpu_firmware_header {TYPE_1__ common; } ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */

bool amdgpu_ucode_hdr_version(union amdgpu_firmware_header *hdr,
				uint16_t hdr_major, uint16_t hdr_minor)
{
	if ((hdr->common.header_version_major == hdr_major) &&
		(hdr->common.header_version_minor == hdr_minor))
		return false;
	return true;
}