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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {struct ib_fmr_pool* fmr_pool; struct iser_page_vec* page_vec; } ;
struct iser_page_vec {int /*<<< orphan*/  list; TYPE_1__ rsc; int /*<<< orphan*/ * pages; } ;
struct iser_fr_pool {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct iser_fr_desc {int /*<<< orphan*/  list; TYPE_1__ rsc; int /*<<< orphan*/ * pages; } ;
struct iser_device {int /*<<< orphan*/  pd; } ;
struct ib_fmr_pool_param {unsigned int max_pages_per_fmr; unsigned int pool_size; unsigned int dirty_watermark; int access; int /*<<< orphan*/ * flush_function; scalar_t__ cache; int /*<<< orphan*/  page_shift; } ;
struct ib_fmr_pool {int dummy; } ;
struct ib_conn {struct iser_fr_pool fr_pool; struct iser_device* device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct ib_fmr_pool*) ; 
 int PTR_ERR (struct ib_fmr_pool*) ; 
 int /*<<< orphan*/  SHIFT_4K ; 
 struct ib_fmr_pool* ib_create_fmr_pool (int /*<<< orphan*/ ,struct ib_fmr_pool_param*) ; 
 int /*<<< orphan*/  iser_err (char*,int) ; 
 int /*<<< orphan*/  kfree (struct iser_page_vec*) ; 
 struct iser_page_vec* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct iser_page_vec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int iser_alloc_fmr_pool(struct ib_conn *ib_conn,
			unsigned cmds_max,
			unsigned int size)
{
	struct iser_device *device = ib_conn->device;
	struct iser_fr_pool *fr_pool = &ib_conn->fr_pool;
	struct iser_page_vec *page_vec;
	struct iser_fr_desc *desc;
	struct ib_fmr_pool *fmr_pool;
	struct ib_fmr_pool_param params;
	int ret;

	INIT_LIST_HEAD(&fr_pool->list);
	spin_lock_init(&fr_pool->lock);

	desc = kzalloc(sizeof(*desc), GFP_KERNEL);
	if (!desc)
		return -ENOMEM;

	page_vec = kmalloc(sizeof(*page_vec) + (sizeof(u64) * size),
			   GFP_KERNEL);
	if (!page_vec) {
		ret = -ENOMEM;
		goto err_frpl;
	}

	page_vec->pages = (u64 *)(page_vec + 1);

	params.page_shift        = SHIFT_4K;
	params.max_pages_per_fmr = size;
	/* make the pool size twice the max number of SCSI commands *
	 * the ML is expected to queue, watermark for unmap at 50%  */
	params.pool_size	 = cmds_max * 2;
	params.dirty_watermark	 = cmds_max;
	params.cache		 = 0;
	params.flush_function	 = NULL;
	params.access		 = (IB_ACCESS_LOCAL_WRITE  |
				    IB_ACCESS_REMOTE_WRITE |
				    IB_ACCESS_REMOTE_READ);

	fmr_pool = ib_create_fmr_pool(device->pd, &params);
	if (IS_ERR(fmr_pool)) {
		ret = PTR_ERR(fmr_pool);
		iser_err("FMR allocation failed, err %d\n", ret);
		goto err_fmr;
	}

	desc->rsc.page_vec = page_vec;
	desc->rsc.fmr_pool = fmr_pool;
	list_add(&desc->list, &fr_pool->list);

	return 0;

err_fmr:
	kfree(page_vec);
err_frpl:
	kfree(desc);

	return ret;
}