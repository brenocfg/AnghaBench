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
struct TYPE_2__ {scalar_t__ phase; scalar_t__ build; } ;
struct bfi_ioc_image_hdr {TYPE_1__ fwver; } ;

/* Variables and functions */

__attribute__((used)) static bool
fwhdr_is_ga(struct bfi_ioc_image_hdr *fwhdr)
{
	if (fwhdr->fwver.phase == 0 &&
	    fwhdr->fwver.build == 0)
		return false;

	return true;
}