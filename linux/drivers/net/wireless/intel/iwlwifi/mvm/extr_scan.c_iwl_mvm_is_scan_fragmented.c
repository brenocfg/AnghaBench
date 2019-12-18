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
typedef  enum iwl_mvm_scan_type { ____Placeholder_iwl_mvm_scan_type } iwl_mvm_scan_type ;

/* Variables and functions */
 int IWL_SCAN_TYPE_FAST_BALANCE ; 
 int IWL_SCAN_TYPE_FRAGMENTED ; 

__attribute__((used)) static bool iwl_mvm_is_scan_fragmented(enum iwl_mvm_scan_type type)
{
	return (type == IWL_SCAN_TYPE_FRAGMENTED ||
		type == IWL_SCAN_TYPE_FAST_BALANCE);
}