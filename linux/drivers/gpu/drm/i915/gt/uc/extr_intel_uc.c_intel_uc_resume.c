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

int intel_uc_resume(struct intel_uc *uc)
{
	/*
	 * When coming out of S3/S4 we sanitize and re-init the HW, so
	 * communication is already re-enabled at this point.
	 */
	return __uc_resume(uc, false);
}