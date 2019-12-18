#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct iwl_scan_req_umac {TYPE_1__ v1; TYPE_4__ v6; TYPE_3__ v7; TYPE_2__ v8; } ;
struct iwl_mvm {struct iwl_scan_req_umac* scan_cmd; } ;

/* Variables and functions */
 scalar_t__ iwl_mvm_cdb_scan_api (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_adaptive_dwell_supported (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_adaptive_dwell_v2_supported (struct iwl_mvm*) ; 

__attribute__((used)) static inline void *iwl_mvm_get_scan_req_umac_data(struct iwl_mvm *mvm)
{
	struct iwl_scan_req_umac *cmd = mvm->scan_cmd;

	if (iwl_mvm_is_adaptive_dwell_v2_supported(mvm))
		return (void *)&cmd->v8.data;

	if (iwl_mvm_is_adaptive_dwell_supported(mvm))
		return (void *)&cmd->v7.data;

	if (iwl_mvm_cdb_scan_api(mvm))
		return (void *)&cmd->v6.data;

	return (void *)&cmd->v1.data;
}