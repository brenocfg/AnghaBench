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
struct intel_vgpu_page_track {int dummy; } ;
struct intel_vgpu {int /*<<< orphan*/  page_track_tree; } ;

/* Variables and functions */
 struct intel_vgpu_page_track* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 

struct intel_vgpu_page_track *intel_vgpu_find_page_track(
		struct intel_vgpu *vgpu, unsigned long gfn)
{
	return radix_tree_lookup(&vgpu->page_track_tree, gfn);
}