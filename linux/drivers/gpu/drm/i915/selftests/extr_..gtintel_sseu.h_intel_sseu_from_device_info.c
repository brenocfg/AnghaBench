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
struct sseu_dev_info {int /*<<< orphan*/  max_eus_per_subslice; int /*<<< orphan*/ * subslice_mask; int /*<<< orphan*/  slice_mask; } ;
struct intel_sseu {int /*<<< orphan*/  max_eus_per_subslice; int /*<<< orphan*/  min_eus_per_subslice; int /*<<< orphan*/  subslice_mask; int /*<<< orphan*/  slice_mask; } ;

/* Variables and functions */

__attribute__((used)) static inline struct intel_sseu
intel_sseu_from_device_info(const struct sseu_dev_info *sseu)
{
	struct intel_sseu value = {
		.slice_mask = sseu->slice_mask,
		.subslice_mask = sseu->subslice_mask[0],
		.min_eus_per_subslice = sseu->max_eus_per_subslice,
		.max_eus_per_subslice = sseu->max_eus_per_subslice,
	};

	return value;
}