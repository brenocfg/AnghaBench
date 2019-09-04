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
struct io_pgtable_cfg {int quirks; } ;
typedef  int /*<<< orphan*/  arm_lpae_iopte ;

/* Variables and functions */
 int IO_PGTABLE_QUIRK_NO_DMA ; 
 int /*<<< orphan*/  __arm_lpae_sync_pte (int /*<<< orphan*/ *,struct io_pgtable_cfg*) ; 

__attribute__((used)) static void __arm_lpae_set_pte(arm_lpae_iopte *ptep, arm_lpae_iopte pte,
			       struct io_pgtable_cfg *cfg)
{
	*ptep = pte;

	if (!(cfg->quirks & IO_PGTABLE_QUIRK_NO_DMA))
		__arm_lpae_sync_pte(ptep, cfg);
}