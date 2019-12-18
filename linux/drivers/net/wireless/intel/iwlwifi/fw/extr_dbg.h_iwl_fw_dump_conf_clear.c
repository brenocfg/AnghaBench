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
struct TYPE_2__ {int /*<<< orphan*/  conf; } ;
struct iwl_fw_runtime {TYPE_1__ dump; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DBG_INVALID ; 

__attribute__((used)) static inline void iwl_fw_dump_conf_clear(struct iwl_fw_runtime *fwrt)
{
	fwrt->dump.conf = FW_DBG_INVALID;
}