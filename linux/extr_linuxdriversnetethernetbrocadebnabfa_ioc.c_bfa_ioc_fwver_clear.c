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
typedef  scalar_t__ u32 ;
struct bfi_ioc_image_hdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ smem_page_start; scalar_t__ host_page_num_fn; int /*<<< orphan*/  smem_pg0; } ;
struct bfa_ioc {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 scalar_t__ PSS_SMEM_PGNUM (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PSS_SMEM_PGOFF (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
bfa_ioc_fwver_clear(struct bfa_ioc *ioc)
{
	u32 pgnum, pgoff, loff = 0;
	int i;

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, loff);
	pgoff = PSS_SMEM_PGOFF(loff);
	writel(pgnum, ioc->ioc_regs.host_page_num_fn);

	for (i = 0; i < (sizeof(struct bfi_ioc_image_hdr) / sizeof(u32)); i++) {
		writel(0, ioc->ioc_regs.smem_page_start + loff);
		loff += sizeof(u32);
	}
}