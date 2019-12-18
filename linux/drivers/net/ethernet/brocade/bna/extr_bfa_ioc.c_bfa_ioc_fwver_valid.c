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
typedef  scalar_t__ u32 ;
struct bfi_ioc_image_hdr {int /*<<< orphan*/  bootenv; } ;
struct bfa_ioc {int dummy; } ;

/* Variables and functions */
 int bfa_nw_ioc_fwver_cmp (struct bfa_ioc*,struct bfi_ioc_image_hdr*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_fwver_get (struct bfa_ioc*,struct bfi_ioc_image_hdr*) ; 
 scalar_t__ swab32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bfa_ioc_fwver_valid(struct bfa_ioc *ioc, u32 boot_env)
{
	struct bfi_ioc_image_hdr fwhdr;

	bfa_nw_ioc_fwver_get(ioc, &fwhdr);
	if (swab32(fwhdr.bootenv) != boot_env)
		return false;

	return bfa_nw_ioc_fwver_cmp(ioc, &fwhdr);
}