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
struct ttm_object_file {struct ttm_object_device* tdev; } ;
struct ttm_object_device {int /*<<< orphan*/  object_lock; int /*<<< orphan*/  idr; } ;
struct ttm_base_object {int shareable; void (* refcount_release ) (struct ttm_base_object**) ;void (* ref_obj_release ) (struct ttm_base_object*,int) ;int object_type; int handle; int /*<<< orphan*/  refcount; int /*<<< orphan*/  tfile; } ;
typedef  enum ttm_object_type { ____Placeholder_ttm_object_type } ttm_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  TTM_REF_USAGE ; 
 int idr_alloc (int /*<<< orphan*/ *,struct ttm_base_object*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_base_object_unref (struct ttm_base_object**) ; 
 int /*<<< orphan*/  ttm_object_file_ref (struct ttm_object_file*) ; 
 int ttm_ref_object_add (struct ttm_object_file*,struct ttm_base_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

int ttm_base_object_init(struct ttm_object_file *tfile,
			 struct ttm_base_object *base,
			 bool shareable,
			 enum ttm_object_type object_type,
			 void (*refcount_release) (struct ttm_base_object **),
			 void (*ref_obj_release) (struct ttm_base_object *,
						  enum ttm_ref_type ref_type))
{
	struct ttm_object_device *tdev = tfile->tdev;
	int ret;

	base->shareable = shareable;
	base->tfile = ttm_object_file_ref(tfile);
	base->refcount_release = refcount_release;
	base->ref_obj_release = ref_obj_release;
	base->object_type = object_type;
	kref_init(&base->refcount);
	idr_preload(GFP_KERNEL);
	spin_lock(&tdev->object_lock);
	ret = idr_alloc(&tdev->idr, base, 1, 0, GFP_NOWAIT);
	spin_unlock(&tdev->object_lock);
	idr_preload_end();
	if (ret < 0)
		return ret;

	base->handle = ret;
	ret = ttm_ref_object_add(tfile, base, TTM_REF_USAGE, NULL, false);
	if (unlikely(ret != 0))
		goto out_err1;

	ttm_base_object_unref(&base);

	return 0;
out_err1:
	spin_lock(&tdev->object_lock);
	idr_remove(&tdev->idr, base->handle);
	spin_unlock(&tdev->object_lock);
	return ret;
}