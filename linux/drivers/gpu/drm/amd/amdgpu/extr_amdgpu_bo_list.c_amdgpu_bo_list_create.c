#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct mm_struct {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_amdgpu_bo_list_entry {int /*<<< orphan*/  bo_priority; int /*<<< orphan*/  bo_handle; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_4__ {TYPE_2__* bo; } ;
struct amdgpu_bo_list_entry {TYPE_1__ tv; int /*<<< orphan*/  priority; } ;
struct amdgpu_bo_list {unsigned int first_userptr; unsigned int num_entries; struct amdgpu_bo* oa_obj; struct amdgpu_bo* gws_obj; struct amdgpu_bo* gds_obj; int /*<<< orphan*/  refcount; } ;
struct TYPE_5__ {int /*<<< orphan*/  ttm; } ;
struct amdgpu_bo {scalar_t__ preferred_domains; TYPE_2__ tbo; } ;
struct TYPE_6__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_BO_LIST_MAX_PRIORITY ; 
 scalar_t__ AMDGPU_GEM_DOMAIN_GDS ; 
 scalar_t__ AMDGPU_GEM_DOMAIN_GWS ; 
 scalar_t__ AMDGPU_GEM_DOMAIN_OA ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SIZE_MAX ; 
 struct amdgpu_bo_list_entry* amdgpu_bo_list_array_entry (struct amdgpu_bo_list*,int /*<<< orphan*/ ) ; 
 struct amdgpu_bo* amdgpu_bo_ref (int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_bo_size (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 struct mm_struct* amdgpu_ttm_tt_get_usermm (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (struct amdgpu_bo_list*) ; 
 struct amdgpu_bo_list* kvmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct amdgpu_bo_list_entry*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_amdgpu_bo_list_set (struct amdgpu_bo_list*,struct amdgpu_bo*) ; 
 int /*<<< orphan*/  trace_amdgpu_cs_bo_status (unsigned int,int /*<<< orphan*/ ) ; 
 struct amdgpu_bo* ttm_to_amdgpu_bo (TYPE_2__*) ; 

int amdgpu_bo_list_create(struct amdgpu_device *adev, struct drm_file *filp,
			  struct drm_amdgpu_bo_list_entry *info,
			  unsigned num_entries, struct amdgpu_bo_list **result)
{
	unsigned last_entry = 0, first_userptr = num_entries;
	struct amdgpu_bo_list_entry *array;
	struct amdgpu_bo_list *list;
	uint64_t total_size = 0;
	size_t size;
	unsigned i;
	int r;

	if (num_entries > (SIZE_MAX - sizeof(struct amdgpu_bo_list))
				/ sizeof(struct amdgpu_bo_list_entry))
		return -EINVAL;

	size = sizeof(struct amdgpu_bo_list);
	size += num_entries * sizeof(struct amdgpu_bo_list_entry);
	list = kvmalloc(size, GFP_KERNEL);
	if (!list)
		return -ENOMEM;

	kref_init(&list->refcount);
	list->gds_obj = NULL;
	list->gws_obj = NULL;
	list->oa_obj = NULL;

	array = amdgpu_bo_list_array_entry(list, 0);
	memset(array, 0, num_entries * sizeof(struct amdgpu_bo_list_entry));

	for (i = 0; i < num_entries; ++i) {
		struct amdgpu_bo_list_entry *entry;
		struct drm_gem_object *gobj;
		struct amdgpu_bo *bo;
		struct mm_struct *usermm;

		gobj = drm_gem_object_lookup(filp, info[i].bo_handle);
		if (!gobj) {
			r = -ENOENT;
			goto error_free;
		}

		bo = amdgpu_bo_ref(gem_to_amdgpu_bo(gobj));
		drm_gem_object_put_unlocked(gobj);

		usermm = amdgpu_ttm_tt_get_usermm(bo->tbo.ttm);
		if (usermm) {
			if (usermm != current->mm) {
				amdgpu_bo_unref(&bo);
				r = -EPERM;
				goto error_free;
			}
			entry = &array[--first_userptr];
		} else {
			entry = &array[last_entry++];
		}

		entry->priority = min(info[i].bo_priority,
				      AMDGPU_BO_LIST_MAX_PRIORITY);
		entry->tv.bo = &bo->tbo;

		if (bo->preferred_domains == AMDGPU_GEM_DOMAIN_GDS)
			list->gds_obj = bo;
		if (bo->preferred_domains == AMDGPU_GEM_DOMAIN_GWS)
			list->gws_obj = bo;
		if (bo->preferred_domains == AMDGPU_GEM_DOMAIN_OA)
			list->oa_obj = bo;

		total_size += amdgpu_bo_size(bo);
		trace_amdgpu_bo_list_set(list, bo);
	}

	list->first_userptr = first_userptr;
	list->num_entries = num_entries;

	trace_amdgpu_cs_bo_status(list->num_entries, total_size);

	*result = list;
	return 0;

error_free:
	for (i = 0; i < last_entry; ++i) {
		struct amdgpu_bo *bo = ttm_to_amdgpu_bo(array[i].tv.bo);

		amdgpu_bo_unref(&bo);
	}
	for (i = first_userptr; i < num_entries; ++i) {
		struct amdgpu_bo *bo = ttm_to_amdgpu_bo(array[i].tv.bo);

		amdgpu_bo_unref(&bo);
	}
	kvfree(list);
	return r;

}