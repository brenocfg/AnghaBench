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
struct TYPE_3__ {unsigned short ppr_able; } ;
typedef  int /*<<< orphan*/  AdvPortAddr ;
typedef  TYPE_1__ ADV_DVC_VAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_MC_PPR_ABLE ; 
 int /*<<< orphan*/  AdvReadWordLram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  AdvWriteWordLram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void advansys_wide_enable_ppr(ADV_DVC_VAR *adv_dvc,
				AdvPortAddr iop_base, unsigned short tidmask)
{
	AdvReadWordLram(iop_base, ASC_MC_PPR_ABLE, adv_dvc->ppr_able);
	adv_dvc->ppr_able |= tidmask;
	AdvWriteWordLram(iop_base, ASC_MC_PPR_ABLE, adv_dvc->ppr_able);
}