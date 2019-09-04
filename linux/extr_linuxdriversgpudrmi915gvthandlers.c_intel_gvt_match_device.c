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
struct intel_gvt {int dummy; } ;

/* Variables and functions */
 unsigned long intel_gvt_get_device_type (struct intel_gvt*) ; 

bool intel_gvt_match_device(struct intel_gvt *gvt,
		unsigned long device)
{
	return intel_gvt_get_device_type(gvt) & device;
}