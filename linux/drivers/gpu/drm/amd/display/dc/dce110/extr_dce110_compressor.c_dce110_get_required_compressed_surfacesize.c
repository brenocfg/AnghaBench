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
struct TYPE_2__ {int preferred_must_be_framebuffer_pool; int min_must_be_framebuffer_pool; } ;
struct fbc_requested_compressed_size {unsigned int preferred_size; unsigned int min_size; int preferred_size_alignment; int min_size_alignment; TYPE_1__ bits; } ;
struct fbc_input_info {scalar_t__ dynamic_fbc_buffer_alloc; } ;

/* Variables and functions */
 unsigned int FBC_MAX_X ; 
 unsigned int FBC_MAX_Y ; 
 unsigned int align_to_chunks_number_per_line (unsigned int) ; 
 int /*<<< orphan*/  get_max_support_fbc_buffersize (unsigned int*,unsigned int*) ; 

bool dce110_get_required_compressed_surfacesize(struct fbc_input_info fbc_input_info,
						struct fbc_requested_compressed_size size)
{
	bool result = false;

	unsigned int max_x = FBC_MAX_X, max_y = FBC_MAX_Y;

	get_max_support_fbc_buffersize(&max_x, &max_y);

	if (fbc_input_info.dynamic_fbc_buffer_alloc == 0) {
		/*
		 * For DCE11 here use Max HW supported size:  HW Support up to 3840x2400 resolution
		 * or 18000 chunks.
		 */
		size.preferred_size = size.min_size = align_to_chunks_number_per_line(max_x) * max_y * 4;  /* (For FBC when LPT not supported). */
		size.preferred_size_alignment = size.min_size_alignment = 0x100;       /* For FBC when LPT not supported */
		size.bits.preferred_must_be_framebuffer_pool = 1;
		size.bits.min_must_be_framebuffer_pool = 1;

		result = true;
	}
	/*
	 * Maybe to add registry key support with optional size here to override above
	 * for debugging purposes
	 */

	return result;
}