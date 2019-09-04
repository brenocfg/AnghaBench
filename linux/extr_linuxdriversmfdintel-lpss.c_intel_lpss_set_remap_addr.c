#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_lpss {scalar_t__ priv; TYPE_2__* info; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
struct TYPE_4__ {TYPE_1__* mem; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 scalar_t__ LPSS_PRIV_REMAP_ADDR ; 
 int /*<<< orphan*/  lo_hi_writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void intel_lpss_set_remap_addr(const struct intel_lpss *lpss)
{
	resource_size_t addr = lpss->info->mem->start;

	lo_hi_writeq(addr, lpss->priv + LPSS_PRIV_REMAP_ADDR);
}