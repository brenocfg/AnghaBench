#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tee_device {TYPE_1__* desc; } ;
struct tee_context {int /*<<< orphan*/  list_shm; struct tee_device* teedev; int /*<<< orphan*/  refcount; } ;
struct TYPE_4__ {int (* open ) (struct tee_context*) ;} ;
struct TYPE_3__ {TYPE_2__* ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct tee_context* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tee_context*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct tee_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct tee_context*) ; 
 int /*<<< orphan*/  tee_device_get (struct tee_device*) ; 
 int /*<<< orphan*/  tee_device_put (struct tee_device*) ; 

__attribute__((used)) static struct tee_context *teedev_open(struct tee_device *teedev)
{
	int rc;
	struct tee_context *ctx;

	if (!tee_device_get(teedev))
		return ERR_PTR(-EINVAL);

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		rc = -ENOMEM;
		goto err;
	}

	kref_init(&ctx->refcount);
	ctx->teedev = teedev;
	INIT_LIST_HEAD(&ctx->list_shm);
	rc = teedev->desc->ops->open(ctx);
	if (rc)
		goto err;

	return ctx;
err:
	kfree(ctx);
	tee_device_put(teedev);
	return ERR_PTR(rc);

}