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
struct amdgpu_device {int dummy; } ;
struct amdgpu_cs_parser {int nchunks; struct amdgpu_cs_chunk* chunks; } ;
struct amdgpu_cs_chunk {int chunk_id; } ;

/* Variables and functions */
#define  AMDGPU_CHUNK_ID_DEPENDENCIES 133 
#define  AMDGPU_CHUNK_ID_SCHEDULED_DEPENDENCIES 132 
#define  AMDGPU_CHUNK_ID_SYNCOBJ_IN 131 
#define  AMDGPU_CHUNK_ID_SYNCOBJ_OUT 130 
#define  AMDGPU_CHUNK_ID_SYNCOBJ_TIMELINE_SIGNAL 129 
#define  AMDGPU_CHUNK_ID_SYNCOBJ_TIMELINE_WAIT 128 
 int amdgpu_cs_process_fence_dep (struct amdgpu_cs_parser*,struct amdgpu_cs_chunk*) ; 
 int amdgpu_cs_process_syncobj_in_dep (struct amdgpu_cs_parser*,struct amdgpu_cs_chunk*) ; 
 int amdgpu_cs_process_syncobj_out_dep (struct amdgpu_cs_parser*,struct amdgpu_cs_chunk*) ; 
 int amdgpu_cs_process_syncobj_timeline_in_dep (struct amdgpu_cs_parser*,struct amdgpu_cs_chunk*) ; 
 int amdgpu_cs_process_syncobj_timeline_out_dep (struct amdgpu_cs_parser*,struct amdgpu_cs_chunk*) ; 

__attribute__((used)) static int amdgpu_cs_dependencies(struct amdgpu_device *adev,
				  struct amdgpu_cs_parser *p)
{
	int i, r;

	for (i = 0; i < p->nchunks; ++i) {
		struct amdgpu_cs_chunk *chunk;

		chunk = &p->chunks[i];

		switch (chunk->chunk_id) {
		case AMDGPU_CHUNK_ID_DEPENDENCIES:
		case AMDGPU_CHUNK_ID_SCHEDULED_DEPENDENCIES:
			r = amdgpu_cs_process_fence_dep(p, chunk);
			if (r)
				return r;
			break;
		case AMDGPU_CHUNK_ID_SYNCOBJ_IN:
			r = amdgpu_cs_process_syncobj_in_dep(p, chunk);
			if (r)
				return r;
			break;
		case AMDGPU_CHUNK_ID_SYNCOBJ_OUT:
			r = amdgpu_cs_process_syncobj_out_dep(p, chunk);
			if (r)
				return r;
			break;
		case AMDGPU_CHUNK_ID_SYNCOBJ_TIMELINE_WAIT:
			r = amdgpu_cs_process_syncobj_timeline_in_dep(p, chunk);
			if (r)
				return r;
			break;
		case AMDGPU_CHUNK_ID_SYNCOBJ_TIMELINE_SIGNAL:
			r = amdgpu_cs_process_syncobj_timeline_out_dep(p, chunk);
			if (r)
				return r;
			break;
		}
	}

	return 0;
}