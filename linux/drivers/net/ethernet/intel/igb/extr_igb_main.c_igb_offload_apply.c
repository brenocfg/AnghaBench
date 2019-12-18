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
struct igb_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  enable_fqtss (struct igb_adapter*,int) ; 
 int /*<<< orphan*/  igb_config_tx_modes (struct igb_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_any_cbs_enabled (struct igb_adapter*) ; 
 int /*<<< orphan*/  is_any_txtime_enabled (struct igb_adapter*) ; 
 int /*<<< orphan*/  is_fqtss_enabled (struct igb_adapter*) ; 

__attribute__((used)) static void igb_offload_apply(struct igb_adapter *adapter, s32 queue)
{
	if (!is_fqtss_enabled(adapter)) {
		enable_fqtss(adapter, true);
		return;
	}

	igb_config_tx_modes(adapter, queue);

	if (!is_any_cbs_enabled(adapter) && !is_any_txtime_enabled(adapter))
		enable_fqtss(adapter, false);
}