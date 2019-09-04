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
struct agp_segment_priv {int /*<<< orphan*/  prot; int /*<<< orphan*/  pg_count; int /*<<< orphan*/  pg_start; } ;
struct agp_segment {int /*<<< orphan*/  prot; int /*<<< orphan*/  pg_count; int /*<<< orphan*/  pg_start; } ;
struct agp_region {int seg_count; struct agp_segment_priv* seg_list; } ;
struct agp_client {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  agp_add_seg_to_client (struct agp_client*,struct agp_segment_priv**,size_t) ; 
 int /*<<< orphan*/  agp_convert_mmap_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct agp_segment_priv*) ; 
 struct agp_segment_priv** kmalloc (int,int /*<<< orphan*/ ) ; 
 struct agp_segment_priv* kzalloc (int,int /*<<< orphan*/ ) ; 

int agp_create_segment(struct agp_client *client, struct agp_region *region)
{
	struct agp_segment_priv **ret_seg;
	struct agp_segment_priv *seg;
	struct agp_segment *user_seg;
	size_t i;

	seg = kzalloc((sizeof(struct agp_segment_priv) * region->seg_count), GFP_KERNEL);
	if (seg == NULL) {
		kfree(region->seg_list);
		region->seg_list = NULL;
		return -ENOMEM;
	}
	user_seg = region->seg_list;

	for (i = 0; i < region->seg_count; i++) {
		seg[i].pg_start = user_seg[i].pg_start;
		seg[i].pg_count = user_seg[i].pg_count;
		seg[i].prot = agp_convert_mmap_flags(user_seg[i].prot);
	}
	kfree(region->seg_list);
	region->seg_list = NULL;

	ret_seg = kmalloc(sizeof(void *), GFP_KERNEL);
	if (ret_seg == NULL) {
		kfree(seg);
		return -ENOMEM;
	}
	*ret_seg = seg;
	agp_add_seg_to_client(client, ret_seg, region->seg_count);
	return 0;
}