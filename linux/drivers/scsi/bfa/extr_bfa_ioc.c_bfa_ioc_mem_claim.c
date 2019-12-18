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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct bfi_ioc_attr_s {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pa; int /*<<< orphan*/ * kva; } ;
struct bfa_ioc_s {struct bfi_ioc_attr_s* attr; TYPE_1__ attr_dma; } ;

/* Variables and functions */

void
bfa_ioc_mem_claim(struct bfa_ioc_s *ioc,  u8 *dm_kva, u64 dm_pa)
{
	/*
	 * dma memory for firmware attribute
	 */
	ioc->attr_dma.kva = dm_kva;
	ioc->attr_dma.pa = dm_pa;
	ioc->attr = (struct bfi_ioc_attr_s *) dm_kva;
}