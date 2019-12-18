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
struct ocxl_fn {int dummy; } ;
struct ocxl_afu {struct ocxl_fn* fn; int /*<<< orphan*/  contexts_idr; int /*<<< orphan*/  afu_control_lock; int /*<<< orphan*/  contexts_lock; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct ocxl_afu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocxl_fn_get (struct ocxl_fn*) ; 

__attribute__((used)) static struct ocxl_afu *alloc_afu(struct ocxl_fn *fn)
{
	struct ocxl_afu *afu;

	afu = kzalloc(sizeof(struct ocxl_afu), GFP_KERNEL);
	if (!afu)
		return NULL;

	kref_init(&afu->kref);
	mutex_init(&afu->contexts_lock);
	mutex_init(&afu->afu_control_lock);
	idr_init(&afu->contexts_idr);
	afu->fn = fn;
	ocxl_fn_get(fn);
	return afu;
}