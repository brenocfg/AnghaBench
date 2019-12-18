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
typedef  enum iwl_scan_ebs_status { ____Placeholder_iwl_scan_ebs_status } iwl_scan_ebs_status ;

/* Variables and functions */
#define  IWL_SCAN_EBS_CHAN_NOT_FOUND 131 
#define  IWL_SCAN_EBS_FAILED 130 
#define  IWL_SCAN_EBS_INACTIVE 129 
#define  IWL_SCAN_EBS_SUCCESS 128 

__attribute__((used)) static const char *iwl_mvm_ebs_status_str(enum iwl_scan_ebs_status status)
{
	switch (status) {
	case IWL_SCAN_EBS_SUCCESS:
		return "successful";
	case IWL_SCAN_EBS_INACTIVE:
		return "inactive";
	case IWL_SCAN_EBS_FAILED:
	case IWL_SCAN_EBS_CHAN_NOT_FOUND:
	default:
		return "failed";
	}
}