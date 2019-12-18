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
struct TYPE_4__ {scalar_t__ umac_err_id; scalar_t__* lmac_err_id; int /*<<< orphan*/ * desc; } ;
struct TYPE_3__ {int num_lmacs; } ;
struct iwl_fw_runtime {TYPE_2__ dump; TYPE_1__ smem_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_dump_desc_assert ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void iwl_fw_free_dump_desc(struct iwl_fw_runtime *fwrt)
{
	if (fwrt->dump.desc != &iwl_dump_desc_assert)
		kfree(fwrt->dump.desc);
	fwrt->dump.desc = NULL;
	fwrt->dump.lmac_err_id[0] = 0;
	if (fwrt->smem_cfg.num_lmacs > 1)
		fwrt->dump.lmac_err_id[1] = 0;
	fwrt->dump.umac_err_id = 0;
}