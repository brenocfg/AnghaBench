#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pvrdma_cmd_create_cq_resp {int cqe; size_t cq_handle; } ;
union pvrdma_cmd_resp {struct pvrdma_cmd_create_cq_resp create_cq_resp; } ;
struct TYPE_9__ {int /*<<< orphan*/  cmd; } ;
struct pvrdma_cmd_create_cq {int nchunks; int cqe; int /*<<< orphan*/  pdir_dma; int /*<<< orphan*/  ctx_handle; TYPE_1__ hdr; } ;
union pvrdma_cmd_req {struct pvrdma_cmd_create_cq create_cq; } ;
typedef  int /*<<< orphan*/  ucmd ;
typedef  int /*<<< orphan*/  u64 ;
struct pvrdma_dev {int /*<<< orphan*/  num_cqs; TYPE_4__* pdev; int /*<<< orphan*/  cq_tbl_lock; TYPE_3__* dsr; struct pvrdma_cq** cq_tbl; } ;
struct pvrdma_create_cq_resp {size_t cqn; int /*<<< orphan*/  member_0; } ;
struct pvrdma_create_cq {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf_addr; } ;
struct pvrdma_cqe {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  dir_dma; int /*<<< orphan*/ * pages; } ;
struct ib_cq {int cqe; } ;
struct pvrdma_cq {int is_kernel; int offset; size_t cq_handle; int /*<<< orphan*/  umem; TYPE_6__ pdir; struct ib_cq ibcq; int /*<<< orphan*/ * uar; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  free; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  ring_state; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_cq_init_attr {int cqe; } ;
typedef  int /*<<< orphan*/  cq_resp ;
struct TYPE_13__ {int /*<<< orphan*/  uar; scalar_t__ ctx_handle; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int max_cqe; size_t max_cq; } ;
struct TYPE_11__ {TYPE_2__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_cq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVRDMA_CMD_CREATE_CQ ; 
 int /*<<< orphan*/  PVRDMA_CMD_CREATE_CQ_RESP ; 
 int PVRDMA_PAGE_DIR_MAX_PAGES ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ ib_copy_from_udata (struct pvrdma_create_cq*,struct ib_udata*,int) ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,struct pvrdma_create_cq_resp*,int) ; 
 int /*<<< orphan*/  ib_umem_get (struct ib_ucontext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ib_umem_page_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pvrdma_cq*) ; 
 struct pvrdma_cq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pvrdma_cmd_create_cq*,int /*<<< orphan*/ ,int) ; 
 int pvrdma_cmd_post (struct pvrdma_dev*,union pvrdma_cmd_req*,union pvrdma_cmd_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_destroy_cq (struct ib_cq*) ; 
 int /*<<< orphan*/  pvrdma_page_dir_cleanup (struct pvrdma_dev*,TYPE_6__*) ; 
 int pvrdma_page_dir_init (struct pvrdma_dev*,TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  pvrdma_page_dir_insert_umem (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pvrdma_dev* to_vdev (struct ib_device*) ; 
 TYPE_5__* to_vucontext (struct ib_ucontext*) ; 

struct ib_cq *pvrdma_create_cq(struct ib_device *ibdev,
			       const struct ib_cq_init_attr *attr,
			       struct ib_ucontext *context,
			       struct ib_udata *udata)
{
	int entries = attr->cqe;
	struct pvrdma_dev *dev = to_vdev(ibdev);
	struct pvrdma_cq *cq;
	int ret;
	int npages;
	unsigned long flags;
	union pvrdma_cmd_req req;
	union pvrdma_cmd_resp rsp;
	struct pvrdma_cmd_create_cq *cmd = &req.create_cq;
	struct pvrdma_cmd_create_cq_resp *resp = &rsp.create_cq_resp;
	struct pvrdma_create_cq_resp cq_resp = {0};
	struct pvrdma_create_cq ucmd;

	BUILD_BUG_ON(sizeof(struct pvrdma_cqe) != 64);

	entries = roundup_pow_of_two(entries);
	if (entries < 1 || entries > dev->dsr->caps.max_cqe)
		return ERR_PTR(-EINVAL);

	if (!atomic_add_unless(&dev->num_cqs, 1, dev->dsr->caps.max_cq))
		return ERR_PTR(-ENOMEM);

	cq = kzalloc(sizeof(*cq), GFP_KERNEL);
	if (!cq) {
		atomic_dec(&dev->num_cqs);
		return ERR_PTR(-ENOMEM);
	}

	cq->ibcq.cqe = entries;
	cq->is_kernel = !context;

	if (!cq->is_kernel) {
		if (ib_copy_from_udata(&ucmd, udata, sizeof(ucmd))) {
			ret = -EFAULT;
			goto err_cq;
		}

		cq->umem = ib_umem_get(context, ucmd.buf_addr, ucmd.buf_size,
				       IB_ACCESS_LOCAL_WRITE, 1);
		if (IS_ERR(cq->umem)) {
			ret = PTR_ERR(cq->umem);
			goto err_cq;
		}

		npages = ib_umem_page_count(cq->umem);
	} else {
		/* One extra page for shared ring state */
		npages = 1 + (entries * sizeof(struct pvrdma_cqe) +
			      PAGE_SIZE - 1) / PAGE_SIZE;

		/* Skip header page. */
		cq->offset = PAGE_SIZE;
	}

	if (npages < 0 || npages > PVRDMA_PAGE_DIR_MAX_PAGES) {
		dev_warn(&dev->pdev->dev,
			 "overflow pages in completion queue\n");
		ret = -EINVAL;
		goto err_umem;
	}

	ret = pvrdma_page_dir_init(dev, &cq->pdir, npages, cq->is_kernel);
	if (ret) {
		dev_warn(&dev->pdev->dev,
			 "could not allocate page directory\n");
		goto err_umem;
	}

	/* Ring state is always the first page. Set in library for user cq. */
	if (cq->is_kernel)
		cq->ring_state = cq->pdir.pages[0];
	else
		pvrdma_page_dir_insert_umem(&cq->pdir, cq->umem, 0);

	refcount_set(&cq->refcnt, 1);
	init_completion(&cq->free);
	spin_lock_init(&cq->cq_lock);

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_CREATE_CQ;
	cmd->nchunks = npages;
	cmd->ctx_handle = (context) ?
		(u64)to_vucontext(context)->ctx_handle : 0;
	cmd->cqe = entries;
	cmd->pdir_dma = cq->pdir.dir_dma;
	ret = pvrdma_cmd_post(dev, &req, &rsp, PVRDMA_CMD_CREATE_CQ_RESP);
	if (ret < 0) {
		dev_warn(&dev->pdev->dev,
			 "could not create completion queue, error: %d\n", ret);
		goto err_page_dir;
	}

	cq->ibcq.cqe = resp->cqe;
	cq->cq_handle = resp->cq_handle;
	cq_resp.cqn = resp->cq_handle;
	spin_lock_irqsave(&dev->cq_tbl_lock, flags);
	dev->cq_tbl[cq->cq_handle % dev->dsr->caps.max_cq] = cq;
	spin_unlock_irqrestore(&dev->cq_tbl_lock, flags);

	if (!cq->is_kernel) {
		cq->uar = &(to_vucontext(context)->uar);

		/* Copy udata back. */
		if (ib_copy_to_udata(udata, &cq_resp, sizeof(cq_resp))) {
			dev_warn(&dev->pdev->dev,
				 "failed to copy back udata\n");
			pvrdma_destroy_cq(&cq->ibcq);
			return ERR_PTR(-EINVAL);
		}
	}

	return &cq->ibcq;

err_page_dir:
	pvrdma_page_dir_cleanup(dev, &cq->pdir);
err_umem:
	if (!cq->is_kernel)
		ib_umem_release(cq->umem);
err_cq:
	atomic_dec(&dev->num_cqs);
	kfree(cq);

	return ERR_PTR(ret);
}