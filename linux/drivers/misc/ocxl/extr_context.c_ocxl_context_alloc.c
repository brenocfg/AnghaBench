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
struct ocxl_context {int pasid; scalar_t__ tidr; int /*<<< orphan*/  irq_idr; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  xsl_error_lock; int /*<<< orphan*/  events_wq; int /*<<< orphan*/  mapping_lock; struct address_space* mapping; int /*<<< orphan*/  status_mutex; int /*<<< orphan*/  status; struct ocxl_afu* afu; } ;
struct ocxl_afu {int /*<<< orphan*/  contexts_lock; int /*<<< orphan*/  pasid_count; scalar_t__ pasid_max; scalar_t__ pasid_base; int /*<<< orphan*/  contexts_idr; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OPENED ; 
 int idr_alloc (int /*<<< orphan*/ *,struct ocxl_context*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct ocxl_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocxl_afu_get (struct ocxl_afu*) ; 

int ocxl_context_alloc(struct ocxl_context **context, struct ocxl_afu *afu,
		struct address_space *mapping)
{
	int pasid;
	struct ocxl_context *ctx;

	*context = kzalloc(sizeof(struct ocxl_context), GFP_KERNEL);
	if (!*context)
		return -ENOMEM;

	ctx = *context;

	ctx->afu = afu;
	mutex_lock(&afu->contexts_lock);
	pasid = idr_alloc(&afu->contexts_idr, ctx, afu->pasid_base,
			afu->pasid_base + afu->pasid_max, GFP_KERNEL);
	if (pasid < 0) {
		mutex_unlock(&afu->contexts_lock);
		return pasid;
	}
	afu->pasid_count++;
	mutex_unlock(&afu->contexts_lock);

	ctx->pasid = pasid;
	ctx->status = OPENED;
	mutex_init(&ctx->status_mutex);
	ctx->mapping = mapping;
	mutex_init(&ctx->mapping_lock);
	init_waitqueue_head(&ctx->events_wq);
	mutex_init(&ctx->xsl_error_lock);
	mutex_init(&ctx->irq_lock);
	idr_init(&ctx->irq_idr);
	ctx->tidr = 0;

	/*
	 * Keep a reference on the AFU to make sure it's valid for the
	 * duration of the life of the context
	 */
	ocxl_afu_get(afu);
	return 0;
}