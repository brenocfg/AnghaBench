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
struct intel_huc {int /*<<< orphan*/  rsa_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_vma_unpin_and_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_huc_rsa_data_destroy(struct intel_huc *huc)
{
	i915_vma_unpin_and_release(&huc->rsa_data, 0);
}