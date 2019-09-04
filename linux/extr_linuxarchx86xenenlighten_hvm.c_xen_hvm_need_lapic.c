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

/* Variables and functions */
 int /*<<< orphan*/  XENFEAT_hvm_pirqs ; 
 scalar_t__ xen_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ xen_have_vector_callback ; 
 int /*<<< orphan*/  xen_hvm_domain () ; 
 scalar_t__ xen_nopv ; 
 scalar_t__ xen_pv_domain () ; 

bool xen_hvm_need_lapic(void)
{
	if (xen_nopv)
		return false;
	if (xen_pv_domain())
		return false;
	if (!xen_hvm_domain())
		return false;
	if (xen_feature(XENFEAT_hvm_pirqs) && xen_have_vector_callback)
		return false;
	return true;
}