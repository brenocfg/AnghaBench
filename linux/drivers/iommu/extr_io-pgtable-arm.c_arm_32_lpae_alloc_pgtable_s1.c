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
struct TYPE_2__ {int tcr; } ;
struct io_pgtable_cfg {int ias; int oas; int pgsize_bitmap; TYPE_1__ arm_lpae_s1_cfg; } ;
struct io_pgtable {int dummy; } ;

/* Variables and functions */
 int ARM_32_LPAE_TCR_EAE ; 
 int SZ_1G ; 
 int SZ_2M ; 
 int SZ_4K ; 
 struct io_pgtable* arm_64_lpae_alloc_pgtable_s1 (struct io_pgtable_cfg*,void*) ; 

__attribute__((used)) static struct io_pgtable *
arm_32_lpae_alloc_pgtable_s1(struct io_pgtable_cfg *cfg, void *cookie)
{
	struct io_pgtable *iop;

	if (cfg->ias > 32 || cfg->oas > 40)
		return NULL;

	cfg->pgsize_bitmap &= (SZ_4K | SZ_2M | SZ_1G);
	iop = arm_64_lpae_alloc_pgtable_s1(cfg, cookie);
	if (iop) {
		cfg->arm_lpae_s1_cfg.tcr |= ARM_32_LPAE_TCR_EAE;
		cfg->arm_lpae_s1_cfg.tcr &= 0xffffffff;
	}

	return iop;
}