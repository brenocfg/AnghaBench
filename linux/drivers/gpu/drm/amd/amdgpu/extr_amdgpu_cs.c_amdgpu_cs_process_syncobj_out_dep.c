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
struct drm_amdgpu_cs_chunk_sem {int /*<<< orphan*/  handle; } ;
struct amdgpu_cs_parser {scalar_t__ num_post_deps; TYPE_1__* post_deps; int /*<<< orphan*/  filp; } ;
struct amdgpu_cs_chunk {int length_dw; scalar_t__ kdata; } ;
struct TYPE_2__ {scalar_t__ point; int /*<<< orphan*/ * chain; int /*<<< orphan*/  syncobj; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_syncobj_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_cs_process_syncobj_out_dep(struct amdgpu_cs_parser *p,
					     struct amdgpu_cs_chunk *chunk)
{
	struct drm_amdgpu_cs_chunk_sem *deps;
	unsigned num_deps;
	int i;

	deps = (struct drm_amdgpu_cs_chunk_sem *)chunk->kdata;
	num_deps = chunk->length_dw * 4 /
		sizeof(struct drm_amdgpu_cs_chunk_sem);

	if (p->post_deps)
		return -EINVAL;

	p->post_deps = kmalloc_array(num_deps, sizeof(*p->post_deps),
				     GFP_KERNEL);
	p->num_post_deps = 0;

	if (!p->post_deps)
		return -ENOMEM;


	for (i = 0; i < num_deps; ++i) {
		p->post_deps[i].syncobj =
			drm_syncobj_find(p->filp, deps[i].handle);
		if (!p->post_deps[i].syncobj)
			return -EINVAL;
		p->post_deps[i].chain = NULL;
		p->post_deps[i].point = 0;
		p->num_post_deps++;
	}

	return 0;
}