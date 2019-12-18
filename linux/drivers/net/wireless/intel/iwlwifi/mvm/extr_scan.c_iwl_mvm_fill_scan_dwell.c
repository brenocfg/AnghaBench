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
struct iwl_scan_dwell {int /*<<< orphan*/  extended; int /*<<< orphan*/  fragmented; int /*<<< orphan*/  passive; int /*<<< orphan*/  active; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_SCAN_DWELL_ACTIVE ; 
 int /*<<< orphan*/  IWL_SCAN_DWELL_EXTENDED ; 
 int /*<<< orphan*/  IWL_SCAN_DWELL_FRAGMENTED ; 
 int /*<<< orphan*/  IWL_SCAN_DWELL_PASSIVE ; 

__attribute__((used)) static void iwl_mvm_fill_scan_dwell(struct iwl_mvm *mvm,
				    struct iwl_scan_dwell *dwell)
{
	dwell->active = IWL_SCAN_DWELL_ACTIVE;
	dwell->passive = IWL_SCAN_DWELL_PASSIVE;
	dwell->fragmented = IWL_SCAN_DWELL_FRAGMENTED;
	dwell->extended = IWL_SCAN_DWELL_EXTENDED;
}