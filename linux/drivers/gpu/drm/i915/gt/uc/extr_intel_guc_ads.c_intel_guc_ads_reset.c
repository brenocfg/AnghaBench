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
struct intel_guc {int /*<<< orphan*/  ads_vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  __guc_ads_init (struct intel_guc*) ; 

void intel_guc_ads_reset(struct intel_guc *guc)
{
	if (!guc->ads_vma)
		return;
	__guc_ads_init(guc);
}