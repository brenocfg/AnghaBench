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
struct TYPE_2__ {int features; int misc_features; } ;

/* Variables and functions */
 int HV_FEATURE_FREQUENCY_MSRS_AVAILABLE ; 
 int HV_X64_ACCESS_FREQUENCY_MSRS ; 
 int HV_X64_ACCESS_REENLIGHTENMENT ; 
 TYPE_1__ ms_hyperv ; 

__attribute__((used)) static inline bool hv_reenlightenment_available(void)
{
	/*
	 * Check for required features and priviliges to make TSC frequency
	 * change notifications work.
	 */
	return ms_hyperv.features & HV_X64_ACCESS_FREQUENCY_MSRS &&
		ms_hyperv.misc_features & HV_FEATURE_FREQUENCY_MSRS_AVAILABLE &&
		ms_hyperv.features & HV_X64_ACCESS_REENLIGHTENMENT;
}