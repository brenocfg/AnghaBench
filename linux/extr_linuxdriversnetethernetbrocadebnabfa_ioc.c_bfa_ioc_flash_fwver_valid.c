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
struct TYPE_2__ {int major; } ;
struct bfi_ioc_image_hdr {TYPE_1__ fwver; } ;

/* Variables and functions */

__attribute__((used)) static bool
bfa_ioc_flash_fwver_valid(struct bfi_ioc_image_hdr *flash_fwhdr)
{
	if (flash_fwhdr->fwver.major == 0 || flash_fwhdr->fwver.major == 0xFF)
		return false;

	return true;
}