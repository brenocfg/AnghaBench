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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ va; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t OMAP4430_INVALID_PRCM_PARTITION ; 
 size_t OMAP4_MAX_PRCM_PARTITIONS ; 
 TYPE_1__* _cm_bases ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void omap4_cminst_write_inst_reg(u32 val, u8 part, u16 inst, u16 idx)
{
	BUG_ON(part >= OMAP4_MAX_PRCM_PARTITIONS ||
	       part == OMAP4430_INVALID_PRCM_PARTITION ||
	       !_cm_bases[part].va);
	writel_relaxed(val, _cm_bases[part].va + inst + idx);
}