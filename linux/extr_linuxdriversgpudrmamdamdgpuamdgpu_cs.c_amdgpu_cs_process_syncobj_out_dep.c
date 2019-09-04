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
struct drm_syncobj {int dummy; } ;
struct drm_amdgpu_cs_chunk_sem {int /*<<< orphan*/  handle; } ;
struct amdgpu_cs_parser {scalar_t__ num_post_dep_syncobjs; int /*<<< orphan*/ * post_dep_syncobjs; int /*<<< orphan*/  filp; } ;
struct amdgpu_cs_chunk {int length_dw; scalar_t__ kdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_syncobj_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_cs_process_syncobj_out_dep(struct amdgpu_cs_parser *p,
					     struct amdgpu_cs_chunk *chunk)
{
	unsigned num_deps;
	int i;
	struct drm_amdgpu_cs_chunk_sem *deps;
	deps = (struct drm_amdgpu_cs_chunk_sem *)chunk->kdata;
	num_deps = chunk->length_dw * 4 /
		sizeof(struct drm_amdgpu_cs_chunk_sem);

	p->post_dep_syncobjs = kmalloc_array(num_deps,
					     sizeof(struct drm_syncobj *),
					     GFP_KERNEL);
	p->num_post_dep_syncobjs = 0;

	if (!p->post_dep_syncobjs)
		return -ENOMEM;

	for (i = 0; i < num_deps; ++i) {
		p->post_dep_syncobjs[i] = drm_syncobj_find(p->filp, deps[i].handle);
		if (!p->post_dep_syncobjs[i])
			return -EINVAL;
		p->num_post_dep_syncobjs++;
	}
	return 0;
}