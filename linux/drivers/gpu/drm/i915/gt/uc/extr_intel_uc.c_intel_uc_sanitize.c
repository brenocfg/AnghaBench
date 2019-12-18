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
 int /*<<< orphan*/  __uc_sanitize (struct intel_uc*) ; 
 int /*<<< orphan*/  intel_uc_supports_guc (struct intel_uc*) ; 

void intel_uc_sanitize(struct intel_uc *uc)
{
	if (!intel_uc_supports_guc(uc))
		return;

	__uc_sanitize(uc);
}