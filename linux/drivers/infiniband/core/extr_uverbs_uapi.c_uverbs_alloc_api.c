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
struct uverbs_api {int /*<<< orphan*/  driver_id; int /*<<< orphan*/  radix; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver_id; } ;
struct ib_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  driver_def; TYPE_1__ ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct uverbs_api* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct uverbs_api* kzalloc (int,int /*<<< orphan*/ ) ; 
 int uapi_finalize (struct uverbs_api*) ; 
 int /*<<< orphan*/  uapi_finalize_disable (struct uverbs_api*) ; 
 int uapi_merge_def (struct uverbs_api*,struct ib_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uverbs_core_api ; 
 int /*<<< orphan*/  uverbs_destroy_api (struct uverbs_api*) ; 

struct uverbs_api *uverbs_alloc_api(struct ib_device *ibdev)
{
	struct uverbs_api *uapi;
	int rc;

	uapi = kzalloc(sizeof(*uapi), GFP_KERNEL);
	if (!uapi)
		return ERR_PTR(-ENOMEM);

	INIT_RADIX_TREE(&uapi->radix, GFP_KERNEL);
	uapi->driver_id = ibdev->ops.driver_id;

	rc = uapi_merge_def(uapi, ibdev, uverbs_core_api, false);
	if (rc)
		goto err;
	rc = uapi_merge_def(uapi, ibdev, ibdev->driver_def, true);
	if (rc)
		goto err;

	uapi_finalize_disable(uapi);
	rc = uapi_finalize(uapi);
	if (rc)
		goto err;

	return uapi;
err:
	if (rc != -ENOMEM)
		dev_err(&ibdev->dev,
			"Setup of uverbs_api failed, kernel parsing tree description is not valid (%d)??\n",
			rc);

	uverbs_destroy_api(uapi);
	return ERR_PTR(rc);
}