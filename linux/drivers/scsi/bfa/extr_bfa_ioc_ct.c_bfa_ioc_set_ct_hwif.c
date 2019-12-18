#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_ioc_s {TYPE_1__* ioc_hwif; } ;
struct TYPE_3__ {int /*<<< orphan*/  ioc_isr_mode_set; int /*<<< orphan*/  ioc_map_port; int /*<<< orphan*/  ioc_reg_init; int /*<<< orphan*/  ioc_pll_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_ioc_ct_isr_mode_set ; 
 int /*<<< orphan*/  bfa_ioc_ct_map_port ; 
 int /*<<< orphan*/  bfa_ioc_ct_pll_init ; 
 int /*<<< orphan*/  bfa_ioc_ct_reg_init ; 
 int /*<<< orphan*/  bfa_ioc_set_ctx_hwif (struct bfa_ioc_s*,TYPE_1__*) ; 
 TYPE_1__ hwif_ct ; 

void
bfa_ioc_set_ct_hwif(struct bfa_ioc_s *ioc)
{
	bfa_ioc_set_ctx_hwif(ioc, &hwif_ct);

	hwif_ct.ioc_pll_init = bfa_ioc_ct_pll_init;
	hwif_ct.ioc_reg_init = bfa_ioc_ct_reg_init;
	hwif_ct.ioc_map_port = bfa_ioc_ct_map_port;
	hwif_ct.ioc_isr_mode_set = bfa_ioc_ct_isr_mode_set;
	ioc->ioc_hwif = &hwif_ct;
}