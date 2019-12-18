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
struct drm_amdgpu_cs_chunk_syncobj {scalar_t__ point; int /*<<< orphan*/  handle; } ;
struct amdgpu_cs_post_dep {scalar_t__ point; int /*<<< orphan*/ * chain; int /*<<< orphan*/  syncobj; } ;
struct amdgpu_cs_parser {scalar_t__ num_post_deps; int /*<<< orphan*/  filp; struct amdgpu_cs_post_dep* post_deps; } ;
struct amdgpu_cs_chunk {int length_dw; scalar_t__ kdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_syncobj_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 struct amdgpu_cs_post_dep* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_cs_process_syncobj_timeline_out_dep(struct amdgpu_cs_parser *p,
						      struct amdgpu_cs_chunk *chunk)
{
	struct drm_amdgpu_cs_chunk_syncobj *syncobj_deps;
	unsigned num_deps;
	int i;

	syncobj_deps = (struct drm_amdgpu_cs_chunk_syncobj *)chunk->kdata;
	num_deps = chunk->length_dw * 4 /
		sizeof(struct drm_amdgpu_cs_chunk_syncobj);

	if (p->post_deps)
		return -EINVAL;

	p->post_deps = kmalloc_array(num_deps, sizeof(*p->post_deps),
				     GFP_KERNEL);
	p->num_post_deps = 0;

	if (!p->post_deps)
		return -ENOMEM;

	for (i = 0; i < num_deps; ++i) {
		struct amdgpu_cs_post_dep *dep = &p->post_deps[i];

		dep->chain = NULL;
		if (syncobj_deps[i].point) {
			dep->chain = kmalloc(sizeof(*dep->chain), GFP_KERNEL);
			if (!dep->chain)
				return -ENOMEM;
		}

		dep->syncobj = drm_syncobj_find(p->filp,
						syncobj_deps[i].handle);
		if (!dep->syncobj) {
			kfree(dep->chain);
			return -EINVAL;
		}
		dep->point = syncobj_deps[i].point;
		p->num_post_deps++;
	}

	return 0;
}