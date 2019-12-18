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
struct intel_uc {int dummy; } ;

/* Variables and functions */
 int __uc_resume (struct intel_uc*,int) ; 

int intel_uc_runtime_resume(struct intel_uc *uc)
{
	/*
	 * During runtime resume we don't sanitize, so we need to re-init
	 * communication as well.
	 */
	return __uc_resume(uc, true);
}