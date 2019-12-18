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
struct bfi_ioc_image_hdr_s {TYPE_1__ fwver; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 

__attribute__((used)) static bfa_boolean_t
bfa_ioc_flash_fwver_valid(struct bfi_ioc_image_hdr_s *flash_fwhdr)
{
	if (flash_fwhdr->fwver.major == 0 || flash_fwhdr->fwver.major == 0xFF)
		return BFA_FALSE;

	return BFA_TRUE;
}