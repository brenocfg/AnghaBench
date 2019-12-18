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
struct hl_ctx_mgr {int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  ctx_handles; } ;
struct hl_fpriv {struct hl_ctx* ctx; struct hl_ctx_mgr ctx_mgr; } ;
struct hl_device {struct hl_ctx* compute_ctx; int /*<<< orphan*/  dev; } ;
struct hl_ctx {int handle; struct hl_fpriv* hpriv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hl_ctx_init (struct hl_device*,struct hl_ctx*,int) ; 
 int /*<<< orphan*/  hl_hpriv_get (struct hl_fpriv*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct hl_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct hl_ctx*) ; 
 struct hl_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int hl_ctx_create(struct hl_device *hdev, struct hl_fpriv *hpriv)
{
	struct hl_ctx_mgr *mgr = &hpriv->ctx_mgr;
	struct hl_ctx *ctx;
	int rc;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		rc = -ENOMEM;
		goto out_err;
	}

	mutex_lock(&mgr->ctx_lock);
	rc = idr_alloc(&mgr->ctx_handles, ctx, 1, 0, GFP_KERNEL);
	mutex_unlock(&mgr->ctx_lock);

	if (rc < 0) {
		dev_err(hdev->dev, "Failed to allocate IDR for a new CTX\n");
		goto free_ctx;
	}

	ctx->handle = rc;

	rc = hl_ctx_init(hdev, ctx, false);
	if (rc)
		goto remove_from_idr;

	hl_hpriv_get(hpriv);
	ctx->hpriv = hpriv;

	/* TODO: remove for multiple contexts per process */
	hpriv->ctx = ctx;

	/* TODO: remove the following line for multiple process support */
	hdev->compute_ctx = ctx;

	return 0;

remove_from_idr:
	mutex_lock(&mgr->ctx_lock);
	idr_remove(&mgr->ctx_handles, ctx->handle);
	mutex_unlock(&mgr->ctx_lock);
free_ctx:
	kfree(ctx);
out_err:
	return rc;
}