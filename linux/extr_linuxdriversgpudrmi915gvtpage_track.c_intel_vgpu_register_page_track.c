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
struct intel_vgpu_page_track {void* priv_data; int /*<<< orphan*/  handler; } ;
struct intel_vgpu {int /*<<< orphan*/  page_track_tree; } ;
typedef  int /*<<< orphan*/  gvt_page_track_handler_t ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct intel_vgpu_page_track* intel_vgpu_find_page_track (struct intel_vgpu*,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct intel_vgpu_page_track*) ; 
 struct intel_vgpu_page_track* kzalloc (int,int /*<<< orphan*/ ) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,unsigned long,struct intel_vgpu_page_track*) ; 

int intel_vgpu_register_page_track(struct intel_vgpu *vgpu, unsigned long gfn,
		gvt_page_track_handler_t handler, void *priv)
{
	struct intel_vgpu_page_track *track;
	int ret;

	track = intel_vgpu_find_page_track(vgpu, gfn);
	if (track)
		return -EEXIST;

	track = kzalloc(sizeof(*track), GFP_KERNEL);
	if (!track)
		return -ENOMEM;

	track->handler = handler;
	track->priv_data = priv;

	ret = radix_tree_insert(&vgpu->page_track_tree, gfn, track);
	if (ret) {
		kfree(track);
		return ret;
	}

	return 0;
}