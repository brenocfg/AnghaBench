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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct ceph_file_extent {scalar_t__ fe_off; scalar_t__ fe_len; } ;

/* Variables and functions */

__attribute__((used)) static void prune_extents(struct ceph_file_extent *img_extents,
			  u32 *num_img_extents, u64 overlap)
{
	u32 cnt = *num_img_extents;

	/* drop extents completely beyond the overlap */
	while (cnt && img_extents[cnt - 1].fe_off >= overlap)
		cnt--;

	if (cnt) {
		struct ceph_file_extent *ex = &img_extents[cnt - 1];

		/* trim final overlapping extent */
		if (ex->fe_off + ex->fe_len > overlap)
			ex->fe_len = overlap - ex->fe_off;
	}

	*num_img_extents = cnt;
}