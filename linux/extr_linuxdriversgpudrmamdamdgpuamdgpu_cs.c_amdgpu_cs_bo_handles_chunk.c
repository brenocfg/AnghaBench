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
struct drm_amdgpu_bo_list_in {int /*<<< orphan*/  bo_number; } ;
struct drm_amdgpu_bo_list_entry {int dummy; } ;
struct amdgpu_cs_parser {int /*<<< orphan*/  bo_list; int /*<<< orphan*/  filp; int /*<<< orphan*/  adev; } ;

/* Variables and functions */
 int amdgpu_bo_create_list_entry_array (struct drm_amdgpu_bo_list_in*,struct drm_amdgpu_bo_list_entry**) ; 
 int amdgpu_bo_list_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_amdgpu_bo_list_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (struct drm_amdgpu_bo_list_entry*) ; 

__attribute__((used)) static int amdgpu_cs_bo_handles_chunk(struct amdgpu_cs_parser *p,
				      struct drm_amdgpu_bo_list_in *data)
{
	int r;
	struct drm_amdgpu_bo_list_entry *info = NULL;

	r = amdgpu_bo_create_list_entry_array(data, &info);
	if (r)
		return r;

	r = amdgpu_bo_list_create(p->adev, p->filp, info, data->bo_number,
				  &p->bo_list);
	if (r)
		goto error_free;

	kvfree(info);
	return 0;

error_free:
	if (info)
		kvfree(info);

	return r;
}