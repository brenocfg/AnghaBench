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
typedef  int u64 ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_write_prph_no_grab (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_iowrite_prph64 (int /*<<< orphan*/ ,int,int) ; 

void iwl_write_prph64_no_grab(struct iwl_trans *trans, u64 ofs, u64 val)
{
	trace_iwlwifi_dev_iowrite_prph64(trans->dev, ofs, val);
	iwl_write_prph_no_grab(trans, ofs, val & 0xffffffff);
	iwl_write_prph_no_grab(trans, ofs + 4, val >> 32);
}