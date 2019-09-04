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
struct uverbs_object_tree_def {int dummy; } ;
struct uverbs_api {int driver_id; int /*<<< orphan*/  radix; } ;
typedef  enum rdma_driver_id { ____Placeholder_rdma_driver_id } rdma_driver_id ;

/* Variables and functions */
 int ENOMEM ; 
 struct uverbs_api* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct uverbs_api* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int uapi_finalize (struct uverbs_api*) ; 
 int uapi_merge_tree (struct uverbs_api*,struct uverbs_object_tree_def const* const,int) ; 
 struct uverbs_object_tree_def const* const uverbs_default_get_objects () ; 
 int /*<<< orphan*/  uverbs_destroy_api (struct uverbs_api*) ; 

struct uverbs_api *uverbs_alloc_api(
	const struct uverbs_object_tree_def *const *driver_specs,
	enum rdma_driver_id driver_id)
{
	struct uverbs_api *uapi;
	int rc;

	uapi = kzalloc(sizeof(*uapi), GFP_KERNEL);
	if (!uapi)
		return ERR_PTR(-ENOMEM);

	INIT_RADIX_TREE(&uapi->radix, GFP_KERNEL);
	uapi->driver_id = driver_id;

	rc = uapi_merge_tree(uapi, uverbs_default_get_objects(), false);
	if (rc)
		goto err;

	for (; driver_specs && *driver_specs; driver_specs++) {
		rc = uapi_merge_tree(uapi, *driver_specs, true);
		if (rc)
			goto err;
	}

	rc = uapi_finalize(uapi);
	if (rc)
		goto err;

	return uapi;
err:
	if (rc != -ENOMEM)
		pr_err("Setup of uverbs_api failed, kernel parsing tree description is not valid (%d)??\n",
		       rc);

	uverbs_destroy_api(uapi);
	return ERR_PTR(rc);
}