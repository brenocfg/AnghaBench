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
struct amdgpu_cs_parser {int num_post_dep_syncobjs; int /*<<< orphan*/  fence; int /*<<< orphan*/ * post_dep_syncobjs; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_syncobj_replace_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amdgpu_cs_post_dependencies(struct amdgpu_cs_parser *p)
{
	int i;

	for (i = 0; i < p->num_post_dep_syncobjs; ++i)
		drm_syncobj_replace_fence(p->post_dep_syncobjs[i], p->fence);
}