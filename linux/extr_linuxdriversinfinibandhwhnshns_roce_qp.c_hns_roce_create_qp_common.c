#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_9__ ;
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_23__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_19__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ucmd ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct ib_udata {int inlen; int outlen; } ;
struct TYPE_29__ {int max_recv_sge; } ;
struct ib_qp_init_attr {scalar_t__ qp_type; scalar_t__ sq_sig_type; int create_flags; TYPE_12__ cap; int /*<<< orphan*/  srq; } ;
struct ib_pd {TYPE_5__* uobject; } ;
struct hns_roce_rinl_wqe {int dummy; } ;
struct hns_roce_rinl_sge {int dummy; } ;
struct TYPE_39__ {int wqe_cnt; TYPE_8__* wqe_list; } ;
struct TYPE_31__ {scalar_t__* db_record; } ;
struct TYPE_33__ {int npages; int page_shift; } ;
struct TYPE_30__ {void* mtt_type; } ;
struct TYPE_36__ {int wqe_cnt; TYPE_8__* wrid; scalar_t__ db_reg_l; int /*<<< orphan*/  lock; } ;
struct TYPE_35__ {int wqe_cnt; TYPE_8__* wrid; scalar_t__ db_reg_l; int /*<<< orphan*/  lock; } ;
struct TYPE_32__ {scalar_t__ qp_type; } ;
struct hns_roce_qp {int sdb_en; int rdb_en; int doorbell_qpn; TYPE_7__ rq_inl_buf; TYPE_19__ rdb; TYPE_23__ hr_buf; int /*<<< orphan*/  buff_size; TYPE_9__* umem; TYPE_15__ mtt; TYPE_19__ sdb; TYPE_4__ rq; TYPE_3__ sq; int /*<<< orphan*/  event; int /*<<< orphan*/  qpn; void* sq_signal_bits; TYPE_1__ ibqp; int /*<<< orphan*/  state; int /*<<< orphan*/  mutex; } ;
struct hns_roce_ib_create_qp_resp {int /*<<< orphan*/  cap_flags; } ;
struct hns_roce_ib_create_qp {int /*<<< orphan*/  db_addr; int /*<<< orphan*/  sdb_addr; int /*<<< orphan*/  buf_addr; } ;
struct TYPE_38__ {int flags; int mtt_buf_pg_sz; } ;
struct TYPE_34__ {int index; } ;
struct hns_roce_dev {scalar_t__ hw_rev; TYPE_6__ caps; TYPE_2__ priv_uar; scalar_t__ odb_offset; scalar_t__ reg_base; scalar_t__ sdb_offset; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
struct TYPE_41__ {int page_shift; } ;
struct TYPE_40__ {struct TYPE_40__* sg_list; } ;
struct TYPE_37__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int DB_REG_OFFSET ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HNS_ROCE_CAP_FLAG_RECORD_DB ; 
 int HNS_ROCE_CAP_FLAG_RQ_INLINE ; 
 int HNS_ROCE_CAP_FLAG_SQ_RECORD_DB ; 
 scalar_t__ HNS_ROCE_HW_VER1 ; 
 int /*<<< orphan*/  HNS_ROCE_SUPPORT_RQ_RECORD_DB ; 
 int /*<<< orphan*/  HNS_ROCE_SUPPORT_SQ_RECORD_DB ; 
 int /*<<< orphan*/  IB_QPS_RESET ; 
 scalar_t__ IB_QPT_GSI ; 
 int IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK ; 
 int IB_QP_CREATE_IPOIB_UD_LSO ; 
 scalar_t__ IB_SIGNAL_ALL_WR ; 
 scalar_t__ IB_SIGNAL_REQ_WR ; 
 scalar_t__ IS_ERR (TYPE_9__*) ; 
 void* MTT_TYPE_WQE ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (TYPE_9__*) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int hns_roce_alloc_db (struct hns_roce_dev*,TYPE_19__*,int /*<<< orphan*/ ) ; 
 scalar_t__ hns_roce_buf_alloc (struct hns_roce_dev*,int /*<<< orphan*/ ,int,TYPE_23__*,int) ; 
 int /*<<< orphan*/  hns_roce_buf_free (struct hns_roce_dev*,int /*<<< orphan*/ ,TYPE_23__*) ; 
 int hns_roce_buf_write_mtt (struct hns_roce_dev*,TYPE_15__*,TYPE_23__*) ; 
 int hns_roce_db_map_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_19__*) ; 
 int /*<<< orphan*/  hns_roce_db_unmap_user (int /*<<< orphan*/ ,TYPE_19__*) ; 
 int /*<<< orphan*/  hns_roce_free_db (struct hns_roce_dev*,TYPE_19__*) ; 
 int hns_roce_gsi_qp_alloc (struct hns_roce_dev*,unsigned long,struct hns_roce_qp*) ; 
 int /*<<< orphan*/  hns_roce_ib_qp_event ; 
 int hns_roce_ib_umem_write_mtt (struct hns_roce_dev*,TYPE_15__*,TYPE_9__*) ; 
 int /*<<< orphan*/  hns_roce_mtt_cleanup (struct hns_roce_dev*,TYPE_15__*) ; 
 int hns_roce_mtt_init (struct hns_roce_dev*,int,int,TYPE_15__*) ; 
 int hns_roce_qp_alloc (struct hns_roce_dev*,unsigned long,struct hns_roce_qp*) ; 
 int /*<<< orphan*/  hns_roce_qp_free (struct hns_roce_dev*,struct hns_roce_qp*) ; 
 scalar_t__ hns_roce_qp_has_rq (struct ib_qp_init_attr*) ; 
 scalar_t__ hns_roce_qp_has_sq (struct ib_qp_init_attr*) ; 
 int /*<<< orphan*/  hns_roce_qp_remove (struct hns_roce_dev*,struct hns_roce_qp*) ; 
 int /*<<< orphan*/  hns_roce_release_range_qp (struct hns_roce_dev*,unsigned long,int) ; 
 int hns_roce_reserve_range_qp (struct hns_roce_dev*,int,int,unsigned long*) ; 
 int hns_roce_set_kernel_sq_size (struct hns_roce_dev*,TYPE_12__*,struct hns_roce_qp*) ; 
 int hns_roce_set_rq_size (struct hns_roce_dev*,TYPE_12__*,int,int,struct hns_roce_qp*) ; 
 int hns_roce_set_user_sq_size (struct hns_roce_dev*,TYPE_12__*,struct hns_roce_qp*,struct hns_roce_ib_create_qp*) ; 
 scalar_t__ ib_copy_from_udata (struct hns_roce_ib_create_qp*,struct ib_udata*,int) ; 
 int ib_copy_to_udata (struct ib_udata*,struct hns_roce_ib_create_qp_resp*,int) ; 
 TYPE_9__* ib_umem_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ib_umem_page_count (TYPE_9__*) ; 
 int /*<<< orphan*/  ib_umem_release (TYPE_9__*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_8__*) ; 
 void* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_hr_ucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_create_qp_common(struct hns_roce_dev *hr_dev,
				     struct ib_pd *ib_pd,
				     struct ib_qp_init_attr *init_attr,
				     struct ib_udata *udata, unsigned long sqpn,
				     struct hns_roce_qp *hr_qp)
{
	struct device *dev = hr_dev->dev;
	struct hns_roce_ib_create_qp ucmd;
	struct hns_roce_ib_create_qp_resp resp = {};
	unsigned long qpn = 0;
	int ret = 0;
	u32 page_shift;
	u32 npages;
	int i;

	mutex_init(&hr_qp->mutex);
	spin_lock_init(&hr_qp->sq.lock);
	spin_lock_init(&hr_qp->rq.lock);

	hr_qp->state = IB_QPS_RESET;

	hr_qp->ibqp.qp_type = init_attr->qp_type;

	if (init_attr->sq_sig_type == IB_SIGNAL_ALL_WR)
		hr_qp->sq_signal_bits = cpu_to_le32(IB_SIGNAL_ALL_WR);
	else
		hr_qp->sq_signal_bits = cpu_to_le32(IB_SIGNAL_REQ_WR);

	ret = hns_roce_set_rq_size(hr_dev, &init_attr->cap, !!ib_pd->uobject,
				   !!init_attr->srq, hr_qp);
	if (ret) {
		dev_err(dev, "hns_roce_set_rq_size failed\n");
		goto err_out;
	}

	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RQ_INLINE) {
		/* allocate recv inline buf */
		hr_qp->rq_inl_buf.wqe_list = kcalloc(hr_qp->rq.wqe_cnt,
					       sizeof(struct hns_roce_rinl_wqe),
					       GFP_KERNEL);
		if (!hr_qp->rq_inl_buf.wqe_list) {
			ret = -ENOMEM;
			goto err_out;
		}

		hr_qp->rq_inl_buf.wqe_cnt = hr_qp->rq.wqe_cnt;

		/* Firstly, allocate a list of sge space buffer */
		hr_qp->rq_inl_buf.wqe_list[0].sg_list =
					kcalloc(hr_qp->rq_inl_buf.wqe_cnt,
					       init_attr->cap.max_recv_sge *
					       sizeof(struct hns_roce_rinl_sge),
					       GFP_KERNEL);
		if (!hr_qp->rq_inl_buf.wqe_list[0].sg_list) {
			ret = -ENOMEM;
			goto err_wqe_list;
		}

		for (i = 1; i < hr_qp->rq_inl_buf.wqe_cnt; i++)
			/* Secondly, reallocate the buffer */
			hr_qp->rq_inl_buf.wqe_list[i].sg_list =
				&hr_qp->rq_inl_buf.wqe_list[0].sg_list[i *
				init_attr->cap.max_recv_sge];
	}

	if (ib_pd->uobject) {
		if (ib_copy_from_udata(&ucmd, udata, sizeof(ucmd))) {
			dev_err(dev, "ib_copy_from_udata error for create qp\n");
			ret = -EFAULT;
			goto err_rq_sge_list;
		}

		ret = hns_roce_set_user_sq_size(hr_dev, &init_attr->cap, hr_qp,
						&ucmd);
		if (ret) {
			dev_err(dev, "hns_roce_set_user_sq_size error for create qp\n");
			goto err_rq_sge_list;
		}

		hr_qp->umem = ib_umem_get(ib_pd->uobject->context,
					  ucmd.buf_addr, hr_qp->buff_size, 0,
					  0);
		if (IS_ERR(hr_qp->umem)) {
			dev_err(dev, "ib_umem_get error for create qp\n");
			ret = PTR_ERR(hr_qp->umem);
			goto err_rq_sge_list;
		}

		hr_qp->mtt.mtt_type = MTT_TYPE_WQE;
		if (hr_dev->caps.mtt_buf_pg_sz) {
			npages = (ib_umem_page_count(hr_qp->umem) +
				  (1 << hr_dev->caps.mtt_buf_pg_sz) - 1) /
				  (1 << hr_dev->caps.mtt_buf_pg_sz);
			page_shift = PAGE_SHIFT + hr_dev->caps.mtt_buf_pg_sz;
			ret = hns_roce_mtt_init(hr_dev, npages,
				    page_shift,
				    &hr_qp->mtt);
		} else {
			ret = hns_roce_mtt_init(hr_dev,
				    ib_umem_page_count(hr_qp->umem),
				    hr_qp->umem->page_shift,
				    &hr_qp->mtt);
		}
		if (ret) {
			dev_err(dev, "hns_roce_mtt_init error for create qp\n");
			goto err_buf;
		}

		ret = hns_roce_ib_umem_write_mtt(hr_dev, &hr_qp->mtt,
						 hr_qp->umem);
		if (ret) {
			dev_err(dev, "hns_roce_ib_umem_write_mtt error for create qp\n");
			goto err_mtt;
		}

		if ((hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SQ_RECORD_DB) &&
		    (udata->inlen >= sizeof(ucmd)) &&
		    (udata->outlen >= sizeof(resp)) &&
		    hns_roce_qp_has_sq(init_attr)) {
			ret = hns_roce_db_map_user(
					to_hr_ucontext(ib_pd->uobject->context),
					ucmd.sdb_addr, &hr_qp->sdb);
			if (ret) {
				dev_err(dev, "sq record doorbell map failed!\n");
				goto err_mtt;
			}

			/* indicate kernel supports sq record db */
			resp.cap_flags |= HNS_ROCE_SUPPORT_SQ_RECORD_DB;
			hr_qp->sdb_en = 1;
		}

		if ((hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB) &&
		    (udata->outlen >= sizeof(resp)) &&
		    hns_roce_qp_has_rq(init_attr)) {
			ret = hns_roce_db_map_user(
					to_hr_ucontext(ib_pd->uobject->context),
					ucmd.db_addr, &hr_qp->rdb);
			if (ret) {
				dev_err(dev, "rq record doorbell map failed!\n");
				goto err_sq_dbmap;
			}
		}
	} else {
		if (init_attr->create_flags &
		    IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK) {
			dev_err(dev, "init_attr->create_flags error!\n");
			ret = -EINVAL;
			goto err_rq_sge_list;
		}

		if (init_attr->create_flags & IB_QP_CREATE_IPOIB_UD_LSO) {
			dev_err(dev, "init_attr->create_flags error!\n");
			ret = -EINVAL;
			goto err_rq_sge_list;
		}

		/* Set SQ size */
		ret = hns_roce_set_kernel_sq_size(hr_dev, &init_attr->cap,
						  hr_qp);
		if (ret) {
			dev_err(dev, "hns_roce_set_kernel_sq_size error!\n");
			goto err_rq_sge_list;
		}

		/* QP doorbell register address */
		hr_qp->sq.db_reg_l = hr_dev->reg_base + hr_dev->sdb_offset +
				     DB_REG_OFFSET * hr_dev->priv_uar.index;
		hr_qp->rq.db_reg_l = hr_dev->reg_base + hr_dev->odb_offset +
				     DB_REG_OFFSET * hr_dev->priv_uar.index;

		if ((hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB) &&
		    hns_roce_qp_has_rq(init_attr)) {
			ret = hns_roce_alloc_db(hr_dev, &hr_qp->rdb, 0);
			if (ret) {
				dev_err(dev, "rq record doorbell alloc failed!\n");
				goto err_rq_sge_list;
			}
			*hr_qp->rdb.db_record = 0;
			hr_qp->rdb_en = 1;
		}

		/* Allocate QP buf */
		page_shift = PAGE_SHIFT + hr_dev->caps.mtt_buf_pg_sz;
		if (hns_roce_buf_alloc(hr_dev, hr_qp->buff_size,
				       (1 << page_shift) * 2,
				       &hr_qp->hr_buf, page_shift)) {
			dev_err(dev, "hns_roce_buf_alloc error!\n");
			ret = -ENOMEM;
			goto err_db;
		}

		hr_qp->mtt.mtt_type = MTT_TYPE_WQE;
		/* Write MTT */
		ret = hns_roce_mtt_init(hr_dev, hr_qp->hr_buf.npages,
					hr_qp->hr_buf.page_shift, &hr_qp->mtt);
		if (ret) {
			dev_err(dev, "hns_roce_mtt_init error for kernel create qp\n");
			goto err_buf;
		}

		ret = hns_roce_buf_write_mtt(hr_dev, &hr_qp->mtt,
					     &hr_qp->hr_buf);
		if (ret) {
			dev_err(dev, "hns_roce_buf_write_mtt error for kernel create qp\n");
			goto err_mtt;
		}

		hr_qp->sq.wrid = kmalloc_array(hr_qp->sq.wqe_cnt, sizeof(u64),
					       GFP_KERNEL);
		hr_qp->rq.wrid = kmalloc_array(hr_qp->rq.wqe_cnt, sizeof(u64),
					       GFP_KERNEL);
		if (!hr_qp->sq.wrid || !hr_qp->rq.wrid) {
			ret = -ENOMEM;
			goto err_wrid;
		}
	}

	if (sqpn) {
		qpn = sqpn;
	} else {
		/* Get QPN */
		ret = hns_roce_reserve_range_qp(hr_dev, 1, 1, &qpn);
		if (ret) {
			dev_err(dev, "hns_roce_reserve_range_qp alloc qpn error\n");
			goto err_wrid;
		}
	}

	if (init_attr->qp_type == IB_QPT_GSI &&
	    hr_dev->hw_rev == HNS_ROCE_HW_VER1) {
		/* In v1 engine, GSI QP context in RoCE engine's register */
		ret = hns_roce_gsi_qp_alloc(hr_dev, qpn, hr_qp);
		if (ret) {
			dev_err(dev, "hns_roce_qp_alloc failed!\n");
			goto err_qpn;
		}
	} else {
		ret = hns_roce_qp_alloc(hr_dev, qpn, hr_qp);
		if (ret) {
			dev_err(dev, "hns_roce_qp_alloc failed!\n");
			goto err_qpn;
		}
	}

	if (sqpn)
		hr_qp->doorbell_qpn = 1;
	else
		hr_qp->doorbell_qpn = cpu_to_le64(hr_qp->qpn);

	if (ib_pd->uobject && (udata->outlen >= sizeof(resp)) &&
		(hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB)) {

		/* indicate kernel supports rq record db */
		resp.cap_flags |= HNS_ROCE_SUPPORT_RQ_RECORD_DB;
		ret = ib_copy_to_udata(udata, &resp, sizeof(resp));
		if (ret)
			goto err_qp;

		hr_qp->rdb_en = 1;
	}
	hr_qp->event = hns_roce_ib_qp_event;

	return 0;

err_qp:
	if (init_attr->qp_type == IB_QPT_GSI &&
		hr_dev->hw_rev == HNS_ROCE_HW_VER1)
		hns_roce_qp_remove(hr_dev, hr_qp);
	else
		hns_roce_qp_free(hr_dev, hr_qp);

err_qpn:
	if (!sqpn)
		hns_roce_release_range_qp(hr_dev, qpn, 1);

err_wrid:
	if (ib_pd->uobject) {
		if ((hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB) &&
		    (udata->outlen >= sizeof(resp)) &&
		    hns_roce_qp_has_rq(init_attr))
			hns_roce_db_unmap_user(
					to_hr_ucontext(ib_pd->uobject->context),
					&hr_qp->rdb);
	} else {
		kfree(hr_qp->sq.wrid);
		kfree(hr_qp->rq.wrid);
	}

err_sq_dbmap:
	if (ib_pd->uobject)
		if ((hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SQ_RECORD_DB) &&
		    (udata->inlen >= sizeof(ucmd)) &&
		    (udata->outlen >= sizeof(resp)) &&
		    hns_roce_qp_has_sq(init_attr))
			hns_roce_db_unmap_user(
					to_hr_ucontext(ib_pd->uobject->context),
					&hr_qp->sdb);

err_mtt:
	hns_roce_mtt_cleanup(hr_dev, &hr_qp->mtt);

err_buf:
	if (ib_pd->uobject)
		ib_umem_release(hr_qp->umem);
	else
		hns_roce_buf_free(hr_dev, hr_qp->buff_size, &hr_qp->hr_buf);

err_db:
	if (!ib_pd->uobject && hns_roce_qp_has_rq(init_attr) &&
	    (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RECORD_DB))
		hns_roce_free_db(hr_dev, &hr_qp->rdb);

err_rq_sge_list:
	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RQ_INLINE)
		kfree(hr_qp->rq_inl_buf.wqe_list[0].sg_list);

err_wqe_list:
	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RQ_INLINE)
		kfree(hr_qp->rq_inl_buf.wqe_list);

err_out:
	return ret;
}