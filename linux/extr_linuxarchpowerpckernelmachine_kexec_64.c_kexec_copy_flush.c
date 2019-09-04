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
struct kimage {long nr_segments; int /*<<< orphan*/  head; int /*<<< orphan*/  segment; } ;
struct kexec_segment {scalar_t__ memsz; scalar_t__ mem; } ;
typedef  int /*<<< orphan*/  ranges ;

/* Variables and functions */
 int KEXEC_SEGMENT_MAX ; 
 scalar_t__ __va (scalar_t__) ; 
 int /*<<< orphan*/  copy_segments (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_icache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  memcpy (struct kexec_segment*,int /*<<< orphan*/ ,int) ; 

void kexec_copy_flush(struct kimage *image)
{
	long i, nr_segments = image->nr_segments;
	struct  kexec_segment ranges[KEXEC_SEGMENT_MAX];

	/* save the ranges on the stack to efficiently flush the icache */
	memcpy(ranges, image->segment, sizeof(ranges));

	/*
	 * After this call we may not use anything allocated in dynamic
	 * memory, including *image.
	 *
	 * Only globals and the stack are allowed.
	 */
	copy_segments(image->head);

	/*
	 * we need to clear the icache for all dest pages sometime,
	 * including ones that were in place on the original copy
	 */
	for (i = 0; i < nr_segments; i++)
		flush_icache_range((unsigned long)__va(ranges[i].mem),
			(unsigned long)__va(ranges[i].mem + ranges[i].memsz));
}