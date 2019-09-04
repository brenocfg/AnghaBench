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
struct TYPE_3__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct cxl_afu {int slice; struct cxl* adapter; int /*<<< orphan*/  irqs_max; int /*<<< orphan*/  prefault_mode; int /*<<< orphan*/  configured_state; int /*<<< orphan*/  afu_cntl_lock; int /*<<< orphan*/  contexts_lock; int /*<<< orphan*/  contexts_idr; TYPE_1__ dev; } ;
struct cxl {int /*<<< orphan*/  user_irqs; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  release_afu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PREFAULT_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* cxl_ops ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 struct cxl_afu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct cxl_afu *cxl_alloc_afu(struct cxl *adapter, int slice)
{
	struct cxl_afu *afu;

	if (!(afu = kzalloc(sizeof(struct cxl_afu), GFP_KERNEL)))
		return NULL;

	afu->adapter = adapter;
	afu->dev.parent = &adapter->dev;
	afu->dev.release = cxl_ops->release_afu;
	afu->slice = slice;
	idr_init(&afu->contexts_idr);
	mutex_init(&afu->contexts_lock);
	spin_lock_init(&afu->afu_cntl_lock);
	atomic_set(&afu->configured_state, -1);
	afu->prefault_mode = CXL_PREFAULT_NONE;
	afu->irqs_max = afu->adapter->user_irqs;

	return afu;
}