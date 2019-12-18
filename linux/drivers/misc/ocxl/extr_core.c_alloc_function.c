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
struct ocxl_fn {int /*<<< orphan*/  actag_list; int /*<<< orphan*/  pasid_list; int /*<<< orphan*/  afu_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ocxl_fn* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ocxl_fn *alloc_function(void)
{
	struct ocxl_fn *fn;

	fn = kzalloc(sizeof(struct ocxl_fn), GFP_KERNEL);
	if (!fn)
		return NULL;

	INIT_LIST_HEAD(&fn->afu_list);
	INIT_LIST_HEAD(&fn->pasid_list);
	INIT_LIST_HEAD(&fn->actag_list);

	return fn;
}