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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_fw_runtime {TYPE_2__* fw; } ;
struct TYPE_3__ {int dump_mask; } ;
struct TYPE_4__ {TYPE_1__ dbg; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool iwl_fw_dbg_type_on(struct iwl_fw_runtime *fwrt, u32 type)
{
	return (fwrt->fw->dbg.dump_mask & BIT(type));
}