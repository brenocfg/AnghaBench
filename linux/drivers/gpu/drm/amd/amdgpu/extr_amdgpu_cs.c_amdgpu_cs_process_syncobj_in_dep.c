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
struct drm_amdgpu_cs_chunk_sem {int /*<<< orphan*/  handle; } ;
struct amdgpu_cs_parser {int dummy; } ;
struct amdgpu_cs_chunk {int length_dw; scalar_t__ kdata; } ;

/* Variables and functions */
 int amdgpu_syncobj_lookup_and_add_to_sync (struct amdgpu_cs_parser*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_cs_process_syncobj_in_dep(struct amdgpu_cs_parser *p,
					    struct amdgpu_cs_chunk *chunk)
{
	struct drm_amdgpu_cs_chunk_sem *deps;
	unsigned num_deps;
	int i, r;

	deps = (struct drm_amdgpu_cs_chunk_sem *)chunk->kdata;
	num_deps = chunk->length_dw * 4 /
		sizeof(struct drm_amdgpu_cs_chunk_sem);
	for (i = 0; i < num_deps; ++i) {
		r = amdgpu_syncobj_lookup_and_add_to_sync(p, deps[i].handle,
							  0, 0);
		if (r)
			return r;
	}

	return 0;
}