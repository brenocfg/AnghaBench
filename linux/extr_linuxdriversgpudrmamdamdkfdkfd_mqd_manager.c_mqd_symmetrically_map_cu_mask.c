#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mqd_manager {TYPE_2__* dev; } ;
struct kfd_cu_info {int cu_active_number; int num_shader_engines; int /*<<< orphan*/ ** cu_bitmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  kgd; TYPE_1__* kfd2kgd; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_cu_info ) (int /*<<< orphan*/ ,struct kfd_cu_info*) ;} ;

/* Variables and functions */
 scalar_t__ hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct kfd_cu_info*) ; 

void mqd_symmetrically_map_cu_mask(struct mqd_manager *mm,
		const uint32_t *cu_mask, uint32_t cu_mask_count,
		uint32_t *se_mask)
{
	struct kfd_cu_info cu_info;
	uint32_t cu_per_sh[4] = {0};
	int i, se, cu = 0;

	mm->dev->kfd2kgd->get_cu_info(mm->dev->kgd, &cu_info);

	if (cu_mask_count > cu_info.cu_active_number)
		cu_mask_count = cu_info.cu_active_number;

	for (se = 0; se < cu_info.num_shader_engines; se++)
		for (i = 0; i < 4; i++)
			cu_per_sh[se] += hweight32(cu_info.cu_bitmap[se][i]);

	/* Symmetrically map cu_mask to all SEs:
	 * cu_mask[0] bit0 -> se_mask[0] bit0;
	 * cu_mask[0] bit1 -> se_mask[1] bit0;
	 * ... (if # SE is 4)
	 * cu_mask[0] bit4 -> se_mask[0] bit1;
	 * ...
	 */
	se = 0;
	for (i = 0; i < cu_mask_count; i++) {
		if (cu_mask[i / 32] & (1 << (i % 32)))
			se_mask[se] |= 1 << cu;

		do {
			se++;
			if (se == cu_info.num_shader_engines) {
				se = 0;
				cu++;
			}
		} while (cu >= cu_per_sh[se] && cu < 32);
	}
}