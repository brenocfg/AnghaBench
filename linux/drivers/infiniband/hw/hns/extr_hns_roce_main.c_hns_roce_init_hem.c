#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  mtt_table; int /*<<< orphan*/  mtt_cqe_table; int /*<<< orphan*/  mtpt_table; int /*<<< orphan*/  mtt_srqwqe_table; int /*<<< orphan*/  mtt_idx_table; } ;
struct TYPE_9__ {int /*<<< orphan*/  qp_table; int /*<<< orphan*/  irrl_table; int /*<<< orphan*/  trrl_table; int /*<<< orphan*/  sccc_table; } ;
struct TYPE_10__ {int mtt_entry_sz; int mtpt_entry_sz; int qpc_entry_sz; int irrl_entry_sz; int max_qp_init_rdma; int trrl_entry_sz; int max_qp_dest_rdma; int cqc_entry_sz; int srqc_entry_sz; int idx_entry_sz; int sccc_entry_sz; int qpc_timer_entry_sz; int cqc_timer_entry_sz; scalar_t__ num_srqwqe_segs; scalar_t__ num_idx_segs; scalar_t__ num_cqc_timer; scalar_t__ num_qpc_timer; scalar_t__ num_qps; scalar_t__ num_srqs; scalar_t__ num_cqs; scalar_t__ num_mtpts; scalar_t__ num_cqe_segs; scalar_t__ num_mtt_segs; } ;
struct TYPE_6__ {int /*<<< orphan*/  table; } ;
struct TYPE_7__ {int /*<<< orphan*/  table; } ;
struct hns_roce_dev {TYPE_3__ mr_table; TYPE_4__ qp_table; TYPE_5__ caps; TYPE_1__ cq_table; TYPE_2__ srq_table; int /*<<< orphan*/  qpc_timer_table; int /*<<< orphan*/  cqc_timer_table; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEM_TYPE_CQC ; 
 int /*<<< orphan*/  HEM_TYPE_CQC_TIMER ; 
 int /*<<< orphan*/  HEM_TYPE_CQE ; 
 int /*<<< orphan*/  HEM_TYPE_IDX ; 
 int /*<<< orphan*/  HEM_TYPE_IRRL ; 
 int /*<<< orphan*/  HEM_TYPE_MTPT ; 
 int /*<<< orphan*/  HEM_TYPE_MTT ; 
 int /*<<< orphan*/  HEM_TYPE_QPC ; 
 int /*<<< orphan*/  HEM_TYPE_QPC_TIMER ; 
 int /*<<< orphan*/  HEM_TYPE_SCCC ; 
 int /*<<< orphan*/  HEM_TYPE_SRQC ; 
 int /*<<< orphan*/  HEM_TYPE_SRQWQE ; 
 int /*<<< orphan*/  HEM_TYPE_TRRL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ hns_roce_check_whether_mhop (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_cleanup_hem_table (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int hns_roce_init_hem_table (struct hns_roce_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,int) ; 

__attribute__((used)) static int hns_roce_init_hem(struct hns_roce_dev *hr_dev)
{
	int ret;
	struct device *dev = hr_dev->dev;

	ret = hns_roce_init_hem_table(hr_dev, &hr_dev->mr_table.mtt_table,
				      HEM_TYPE_MTT, hr_dev->caps.mtt_entry_sz,
				      hr_dev->caps.num_mtt_segs, 1);
	if (ret) {
		dev_err(dev, "Failed to init MTT context memory, aborting.\n");
		return ret;
	}

	if (hns_roce_check_whether_mhop(hr_dev, HEM_TYPE_CQE)) {
		ret = hns_roce_init_hem_table(hr_dev,
				      &hr_dev->mr_table.mtt_cqe_table,
				      HEM_TYPE_CQE, hr_dev->caps.mtt_entry_sz,
				      hr_dev->caps.num_cqe_segs, 1);
		if (ret) {
			dev_err(dev, "Failed to init MTT CQE context memory, aborting.\n");
			goto err_unmap_cqe;
		}
	}

	ret = hns_roce_init_hem_table(hr_dev, &hr_dev->mr_table.mtpt_table,
				      HEM_TYPE_MTPT, hr_dev->caps.mtpt_entry_sz,
				      hr_dev->caps.num_mtpts, 1);
	if (ret) {
		dev_err(dev, "Failed to init MTPT context memory, aborting.\n");
		goto err_unmap_mtt;
	}

	ret = hns_roce_init_hem_table(hr_dev, &hr_dev->qp_table.qp_table,
				      HEM_TYPE_QPC, hr_dev->caps.qpc_entry_sz,
				      hr_dev->caps.num_qps, 1);
	if (ret) {
		dev_err(dev, "Failed to init QP context memory, aborting.\n");
		goto err_unmap_dmpt;
	}

	ret = hns_roce_init_hem_table(hr_dev, &hr_dev->qp_table.irrl_table,
				      HEM_TYPE_IRRL,
				      hr_dev->caps.irrl_entry_sz *
				      hr_dev->caps.max_qp_init_rdma,
				      hr_dev->caps.num_qps, 1);
	if (ret) {
		dev_err(dev, "Failed to init irrl_table memory, aborting.\n");
		goto err_unmap_qp;
	}

	if (hr_dev->caps.trrl_entry_sz) {
		ret = hns_roce_init_hem_table(hr_dev,
					      &hr_dev->qp_table.trrl_table,
					      HEM_TYPE_TRRL,
					      hr_dev->caps.trrl_entry_sz *
					      hr_dev->caps.max_qp_dest_rdma,
					      hr_dev->caps.num_qps, 1);
		if (ret) {
			dev_err(dev,
			       "Failed to init trrl_table memory, aborting.\n");
			goto err_unmap_irrl;
		}
	}

	ret = hns_roce_init_hem_table(hr_dev, &hr_dev->cq_table.table,
				      HEM_TYPE_CQC, hr_dev->caps.cqc_entry_sz,
				      hr_dev->caps.num_cqs, 1);
	if (ret) {
		dev_err(dev, "Failed to init CQ context memory, aborting.\n");
		goto err_unmap_trrl;
	}

	if (hr_dev->caps.srqc_entry_sz) {
		ret = hns_roce_init_hem_table(hr_dev, &hr_dev->srq_table.table,
					      HEM_TYPE_SRQC,
					      hr_dev->caps.srqc_entry_sz,
					      hr_dev->caps.num_srqs, 1);
		if (ret) {
			dev_err(dev,
			      "Failed to init SRQ context memory, aborting.\n");
			goto err_unmap_cq;
		}
	}

	if (hr_dev->caps.num_srqwqe_segs) {
		ret = hns_roce_init_hem_table(hr_dev,
					     &hr_dev->mr_table.mtt_srqwqe_table,
					     HEM_TYPE_SRQWQE,
					     hr_dev->caps.mtt_entry_sz,
					     hr_dev->caps.num_srqwqe_segs, 1);
		if (ret) {
			dev_err(dev,
				"Failed to init MTT srqwqe memory, aborting.\n");
			goto err_unmap_srq;
		}
	}

	if (hr_dev->caps.num_idx_segs) {
		ret = hns_roce_init_hem_table(hr_dev,
					      &hr_dev->mr_table.mtt_idx_table,
					      HEM_TYPE_IDX,
					      hr_dev->caps.idx_entry_sz,
					      hr_dev->caps.num_idx_segs, 1);
		if (ret) {
			dev_err(dev,
				"Failed to init MTT idx memory, aborting.\n");
			goto err_unmap_srqwqe;
		}
	}

	if (hr_dev->caps.sccc_entry_sz) {
		ret = hns_roce_init_hem_table(hr_dev,
					      &hr_dev->qp_table.sccc_table,
					      HEM_TYPE_SCCC,
					      hr_dev->caps.sccc_entry_sz,
					      hr_dev->caps.num_qps, 1);
		if (ret) {
			dev_err(dev,
			      "Failed to init SCC context memory, aborting.\n");
			goto err_unmap_idx;
		}
	}

	if (hr_dev->caps.qpc_timer_entry_sz) {
		ret = hns_roce_init_hem_table(hr_dev,
					      &hr_dev->qpc_timer_table,
					      HEM_TYPE_QPC_TIMER,
					      hr_dev->caps.qpc_timer_entry_sz,
					      hr_dev->caps.num_qpc_timer, 1);
		if (ret) {
			dev_err(dev,
			      "Failed to init QPC timer memory, aborting.\n");
			goto err_unmap_ctx;
		}
	}

	if (hr_dev->caps.cqc_timer_entry_sz) {
		ret = hns_roce_init_hem_table(hr_dev,
					      &hr_dev->cqc_timer_table,
					      HEM_TYPE_CQC_TIMER,
					      hr_dev->caps.cqc_timer_entry_sz,
					      hr_dev->caps.num_cqc_timer, 1);
		if (ret) {
			dev_err(dev,
			      "Failed to init CQC timer memory, aborting.\n");
			goto err_unmap_qpc_timer;
		}
	}

	return 0;

err_unmap_qpc_timer:
	if (hr_dev->caps.qpc_timer_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->qpc_timer_table);

err_unmap_ctx:
	if (hr_dev->caps.sccc_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->qp_table.sccc_table);

err_unmap_idx:
	if (hr_dev->caps.num_idx_segs)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->mr_table.mtt_idx_table);

err_unmap_srqwqe:
	if (hr_dev->caps.num_srqwqe_segs)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->mr_table.mtt_srqwqe_table);

err_unmap_srq:
	if (hr_dev->caps.srqc_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev, &hr_dev->srq_table.table);

err_unmap_cq:
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->cq_table.table);

err_unmap_trrl:
	if (hr_dev->caps.trrl_entry_sz)
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->qp_table.trrl_table);

err_unmap_irrl:
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->qp_table.irrl_table);

err_unmap_qp:
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->qp_table.qp_table);

err_unmap_dmpt:
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->mr_table.mtpt_table);

err_unmap_mtt:
	if (hns_roce_check_whether_mhop(hr_dev, HEM_TYPE_CQE))
		hns_roce_cleanup_hem_table(hr_dev,
					   &hr_dev->mr_table.mtt_cqe_table);

err_unmap_cqe:
	hns_roce_cleanup_hem_table(hr_dev, &hr_dev->mr_table.mtt_table);

	return ret;
}