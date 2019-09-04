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
typedef  scalar_t__ u64 ;
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ib_umem {scalar_t__ length; scalar_t__ hugetlb; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {TYPE_1__* uobject; int /*<<< orphan*/  device; } ;
struct ib_mr {void* lkey; void* rkey; int /*<<< orphan*/  device; struct ib_pd* pd; } ;
struct i40iw_ucontext {int /*<<< orphan*/  cq_reg_mem_list_lock; int /*<<< orphan*/  cq_reg_mem_list; int /*<<< orphan*/  qp_reg_mem_list_lock; int /*<<< orphan*/  qp_reg_mem_list; } ;
struct i40iw_pd {int dummy; } ;
struct i40iw_pble_alloc {scalar_t__ level; } ;
struct i40iw_pbl {int on_list; int pbl_allocated; int /*<<< orphan*/  list; struct i40iw_pble_alloc pble_alloc; scalar_t__ user_base; struct i40iw_mr* iwmr; } ;
struct i40iw_mr {int page_size; scalar_t__ length; int type; int page_cnt; struct ib_mr ibmr; void* stag; int /*<<< orphan*/  page_msk; struct ib_umem* region; struct i40iw_pbl iwpbl; } ;
struct i40iw_mem_reg_req {int reg_type; int sq_pages; int rq_pages; int cq_pages; } ;
struct i40iw_device {int /*<<< orphan*/  pble_rsrc; scalar_t__ closing; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSYS ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I40IW_ACCESS_FLAGS_LOCALREAD ; 
 scalar_t__ I40IW_LEVEL_0 ; 
 scalar_t__ I40IW_MAX_MR_SIZE ; 
 scalar_t__ IS_ERR (struct ib_umem*) ; 
#define  IW_MEMREG_TYPE_CQ 130 
#define  IW_MEMREG_TYPE_MEM 129 
#define  IW_MEMREG_TYPE_QP 128 
 int /*<<< orphan*/  PAGE_MASK ; 
 int PAGE_SIZE ; 
 int ffs (int) ; 
 int /*<<< orphan*/  i40iw_add_pdusecount (struct i40iw_pd*) ; 
 int i40iw_check_mr_contiguous (struct i40iw_pble_alloc*,int) ; 
 void* i40iw_create_stag (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_free_pble (int /*<<< orphan*/ ,struct i40iw_pble_alloc*) ; 
 int /*<<< orphan*/  i40iw_free_stag (struct i40iw_device*,void*) ; 
 int /*<<< orphan*/  i40iw_get_user_access (int) ; 
 int i40iw_handle_q_mem (struct i40iw_device*,struct i40iw_mem_reg_req*,struct i40iw_pbl*,int) ; 
 int i40iw_hwreg_mr (struct i40iw_device*,struct i40iw_mr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_set_hugetlb_values (scalar_t__,struct i40iw_mr*) ; 
 int i40iw_setup_pbles (struct i40iw_device*,struct i40iw_mr*,int) ; 
 scalar_t__ ib_copy_from_udata (struct i40iw_mem_reg_req*,struct ib_udata*,int) ; 
 struct ib_umem* ib_umem_get (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_release (struct ib_umem*) ; 
 int /*<<< orphan*/  kfree (struct i40iw_mr*) ; 
 struct i40iw_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct i40iw_device* to_iwdev (int /*<<< orphan*/ ) ; 
 struct i40iw_pd* to_iwpd (struct ib_pd*) ; 
 struct i40iw_ucontext* to_ucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_mr *i40iw_reg_user_mr(struct ib_pd *pd,
				       u64 start,
				       u64 length,
				       u64 virt,
				       int acc,
				       struct ib_udata *udata)
{
	struct i40iw_pd *iwpd = to_iwpd(pd);
	struct i40iw_device *iwdev = to_iwdev(pd->device);
	struct i40iw_ucontext *ucontext;
	struct i40iw_pble_alloc *palloc;
	struct i40iw_pbl *iwpbl;
	struct i40iw_mr *iwmr;
	struct ib_umem *region;
	struct i40iw_mem_reg_req req;
	u64 pbl_depth = 0;
	u32 stag = 0;
	u16 access;
	u64 region_length;
	bool use_pbles = false;
	unsigned long flags;
	int err = -ENOSYS;
	int ret;
	int pg_shift;

	if (iwdev->closing)
		return ERR_PTR(-ENODEV);

	if (length > I40IW_MAX_MR_SIZE)
		return ERR_PTR(-EINVAL);
	region = ib_umem_get(pd->uobject->context, start, length, acc, 0);
	if (IS_ERR(region))
		return (struct ib_mr *)region;

	if (ib_copy_from_udata(&req, udata, sizeof(req))) {
		ib_umem_release(region);
		return ERR_PTR(-EFAULT);
	}

	iwmr = kzalloc(sizeof(*iwmr), GFP_KERNEL);
	if (!iwmr) {
		ib_umem_release(region);
		return ERR_PTR(-ENOMEM);
	}

	iwpbl = &iwmr->iwpbl;
	iwpbl->iwmr = iwmr;
	iwmr->region = region;
	iwmr->ibmr.pd = pd;
	iwmr->ibmr.device = pd->device;
	ucontext = to_ucontext(pd->uobject->context);

	iwmr->page_size = PAGE_SIZE;
	iwmr->page_msk = PAGE_MASK;

	if (region->hugetlb && (req.reg_type == IW_MEMREG_TYPE_MEM))
		i40iw_set_hugetlb_values(start, iwmr);

	region_length = region->length + (start & (iwmr->page_size - 1));
	pg_shift = ffs(iwmr->page_size) - 1;
	pbl_depth = region_length >> pg_shift;
	pbl_depth += (region_length & (iwmr->page_size - 1)) ? 1 : 0;
	iwmr->length = region->length;

	iwpbl->user_base = virt;
	palloc = &iwpbl->pble_alloc;

	iwmr->type = req.reg_type;
	iwmr->page_cnt = (u32)pbl_depth;

	switch (req.reg_type) {
	case IW_MEMREG_TYPE_QP:
		use_pbles = ((req.sq_pages + req.rq_pages) > 2);
		err = i40iw_handle_q_mem(iwdev, &req, iwpbl, use_pbles);
		if (err)
			goto error;
		spin_lock_irqsave(&ucontext->qp_reg_mem_list_lock, flags);
		list_add_tail(&iwpbl->list, &ucontext->qp_reg_mem_list);
		iwpbl->on_list = true;
		spin_unlock_irqrestore(&ucontext->qp_reg_mem_list_lock, flags);
		break;
	case IW_MEMREG_TYPE_CQ:
		use_pbles = (req.cq_pages > 1);
		err = i40iw_handle_q_mem(iwdev, &req, iwpbl, use_pbles);
		if (err)
			goto error;

		spin_lock_irqsave(&ucontext->cq_reg_mem_list_lock, flags);
		list_add_tail(&iwpbl->list, &ucontext->cq_reg_mem_list);
		iwpbl->on_list = true;
		spin_unlock_irqrestore(&ucontext->cq_reg_mem_list_lock, flags);
		break;
	case IW_MEMREG_TYPE_MEM:
		use_pbles = (iwmr->page_cnt != 1);
		access = I40IW_ACCESS_FLAGS_LOCALREAD;

		err = i40iw_setup_pbles(iwdev, iwmr, use_pbles);
		if (err)
			goto error;

		if (use_pbles) {
			ret = i40iw_check_mr_contiguous(palloc, iwmr->page_size);
			if (ret) {
				i40iw_free_pble(iwdev->pble_rsrc, palloc);
				iwpbl->pbl_allocated = false;
			}
		}

		access |= i40iw_get_user_access(acc);
		stag = i40iw_create_stag(iwdev);
		if (!stag) {
			err = -ENOMEM;
			goto error;
		}

		iwmr->stag = stag;
		iwmr->ibmr.rkey = stag;
		iwmr->ibmr.lkey = stag;

		err = i40iw_hwreg_mr(iwdev, iwmr, access);
		if (err) {
			i40iw_free_stag(iwdev, stag);
			goto error;
		}

		break;
	default:
		goto error;
	}

	iwmr->type = req.reg_type;
	if (req.reg_type == IW_MEMREG_TYPE_MEM)
		i40iw_add_pdusecount(iwpd);
	return &iwmr->ibmr;

error:
	if (palloc->level != I40IW_LEVEL_0 && iwpbl->pbl_allocated)
		i40iw_free_pble(iwdev->pble_rsrc, palloc);
	ib_umem_release(region);
	kfree(iwmr);
	return ERR_PTR(err);
}