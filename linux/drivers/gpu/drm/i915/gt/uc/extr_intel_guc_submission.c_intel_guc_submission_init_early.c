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
struct intel_guc {int /*<<< orphan*/  submission_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  __guc_submission_support (struct intel_guc*) ; 

void intel_guc_submission_init_early(struct intel_guc *guc)
{
	guc->submission_supported = __guc_submission_support(guc);
}