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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct i40e_package_header {size_t segment_count; int* segment_offset; } ;
struct i40e_generic_seg_header {size_t type; } ;

/* Variables and functions */

struct i40e_generic_seg_header *
i40evf_find_segment_in_package(u32 segment_type,
			       struct i40e_package_header *pkg_hdr)
{
	struct i40e_generic_seg_header *segment;
	u32 i;

	/* Search all package segments for the requested segment type */
	for (i = 0; i < pkg_hdr->segment_count; i++) {
		segment =
			(struct i40e_generic_seg_header *)((u8 *)pkg_hdr +
			 pkg_hdr->segment_offset[i]);

		if (segment->type == segment_type)
			return segment;
	}

	return NULL;
}