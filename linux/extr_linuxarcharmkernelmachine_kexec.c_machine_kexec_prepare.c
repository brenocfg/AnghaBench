#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ kernel_r2; } ;
struct kimage {int nr_segments; TYPE_1__ arch; struct kexec_segment* segment; scalar_t__ start; } ;
struct kexec_segment {scalar_t__ mem; scalar_t__ buf; int /*<<< orphan*/  memsz; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ KEXEC_ARM_ATAGS_OFFSET ; 
 scalar_t__ KEXEC_ARM_ZIMAGE_OFFSET ; 
 int /*<<< orphan*/  OF_DT_HEADER ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int get_user (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  idmap_to_phys (scalar_t__) ; 
 int /*<<< orphan*/  memblock_is_region_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int num_possible_cpus () ; 
 int /*<<< orphan*/  platform_can_cpu_hotplug () ; 
 scalar_t__ platform_can_secondary_boot () ; 

int machine_kexec_prepare(struct kimage *image)
{
	struct kexec_segment *current_segment;
	__be32 header;
	int i, err;

	image->arch.kernel_r2 = image->start - KEXEC_ARM_ZIMAGE_OFFSET
				     + KEXEC_ARM_ATAGS_OFFSET;

	/*
	 * Validate that if the current HW supports SMP, then the SW supports
	 * and implements CPU hotplug for the current HW. If not, we won't be
	 * able to kexec reliably, so fail the prepare operation.
	 */
	if (num_possible_cpus() > 1 && platform_can_secondary_boot() &&
	    !platform_can_cpu_hotplug())
		return -EINVAL;

	/*
	 * No segment at default ATAGs address. try to locate
	 * a dtb using magic.
	 */
	for (i = 0; i < image->nr_segments; i++) {
		current_segment = &image->segment[i];

		if (!memblock_is_region_memory(idmap_to_phys(current_segment->mem),
					       current_segment->memsz))
			return -EINVAL;

		err = get_user(header, (__be32*)current_segment->buf);
		if (err)
			return err;

		if (header == cpu_to_be32(OF_DT_HEADER))
			image->arch.kernel_r2 = current_segment->mem;
	}
	return 0;
}