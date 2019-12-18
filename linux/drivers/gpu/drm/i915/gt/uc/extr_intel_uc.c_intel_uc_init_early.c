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
struct intel_uc {int /*<<< orphan*/  huc; int /*<<< orphan*/  guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __confirm_options (struct intel_uc*) ; 
 int /*<<< orphan*/  intel_guc_init_early (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_huc_init_early (int /*<<< orphan*/ *) ; 

void intel_uc_init_early(struct intel_uc *uc)
{
	intel_guc_init_early(&uc->guc);
	intel_huc_init_early(&uc->huc);

	__confirm_options(uc);
}