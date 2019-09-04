#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {size_t level; TYPE_1__* pbl; } ;
struct TYPE_23__ {int /*<<< orphan*/  creq_ring_id; TYPE_2__ creq; } ;
struct TYPE_20__ {int /*<<< orphan*/  fw_id; int /*<<< orphan*/  dma_map; } ;
struct TYPE_24__ {TYPE_4__ stats; } ;
struct TYPE_22__ {int /*<<< orphan*/  dev; } ;
struct bnxt_re_dev {TYPE_8__ rcfw; TYPE_9__ qplib_ctx; TYPE_5__* en_dev; TYPE_6__ ibdev; int /*<<< orphan*/  flags; int /*<<< orphan*/  active_width; int /*<<< orphan*/  active_speed; int /*<<< orphan*/  worker; int /*<<< orphan*/  is_virtfn; int /*<<< orphan*/  dev_attr; TYPE_3__* msix_entries; } ;
struct TYPE_21__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_19__ {int /*<<< orphan*/  db_offset; int /*<<< orphan*/  vector; int /*<<< orphan*/  ring_idx; } ;
struct TYPE_17__ {int /*<<< orphan*/  pg_count; int /*<<< orphan*/  pg_map_arr; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ BNXT_QPLIB_CREQE_MAX_CNT ; 
 size_t BNXT_RE_AEQ_IDX ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_GOT_MSIX ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_IBDEV_REGISTERED ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_ISSUE_ROCE_STATS ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_NETDEV_REGISTERED ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_QOS_WORK_REG ; 
 int /*<<< orphan*/  BNXT_RE_FLAG_RCFW_CHANNEL_EN ; 
 int /*<<< orphan*/  BNXT_RE_MAX_QPC_COUNT ; 
 int EINVAL ; 
 int /*<<< orphan*/  HWRM_RING_ALLOC_CMPL ; 
 int /*<<< orphan*/  IB_EVENT_GID_CHANGE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t PBL_LVL_0 ; 
 int bnxt_qplib_alloc_ctx (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int bnxt_qplib_alloc_rcfw_channel (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_qplib_disable_rcfw_channel (TYPE_8__*) ; 
 int bnxt_qplib_enable_rcfw_channel (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_qplib_free_ctx (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  bnxt_qplib_free_rcfw_channel (TYPE_8__*) ; 
 int bnxt_qplib_get_dev_attr (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bnxt_qplib_init_rcfw (TYPE_8__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_re_aeq_handler ; 
 int bnxt_re_alloc_res (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/ * bnxt_re_attributes ; 
 int /*<<< orphan*/  bnxt_re_dispatch_event (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_re_get_sriov_func_type (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_ib_unreg (struct bnxt_re_dev*) ; 
 int bnxt_re_init_res (struct bnxt_re_dev*) ; 
 int bnxt_re_net_ring_alloc (struct bnxt_re_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_re_net_ring_free (struct bnxt_re_dev*,int /*<<< orphan*/ ) ; 
 int bnxt_re_net_stats_ctx_alloc (struct bnxt_re_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_re_net_stats_ctx_free (struct bnxt_re_dev*,int /*<<< orphan*/ ) ; 
 int bnxt_re_register_ib (struct bnxt_re_dev*) ; 
 int bnxt_re_register_netdev (struct bnxt_re_dev*) ; 
 int bnxt_re_request_msix (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_set_resource_limits (struct bnxt_re_dev*) ; 
 int bnxt_re_setup_qos (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_unregister_ib (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_worker ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_get_eth_speed (TYPE_6__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  rdev_to_dev (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_re_ib_reg(struct bnxt_re_dev *rdev)
{
	int i, j, rc;

	bool locked;

	/* Acquire rtnl lock through out this function */
	rtnl_lock();
	locked = true;

	/* Registered a new RoCE device instance to netdev */
	rc = bnxt_re_register_netdev(rdev);
	if (rc) {
		rtnl_unlock();
		pr_err("Failed to register with netedev: %#x\n", rc);
		return -EINVAL;
	}
	set_bit(BNXT_RE_FLAG_NETDEV_REGISTERED, &rdev->flags);

	/* Check whether VF or PF */
	bnxt_re_get_sriov_func_type(rdev);

	rc = bnxt_re_request_msix(rdev);
	if (rc) {
		pr_err("Failed to get MSI-X vectors: %#x\n", rc);
		rc = -EINVAL;
		goto fail;
	}
	set_bit(BNXT_RE_FLAG_GOT_MSIX, &rdev->flags);

	/* Establish RCFW Communication Channel to initialize the context
	 * memory for the function and all child VFs
	 */
	rc = bnxt_qplib_alloc_rcfw_channel(rdev->en_dev->pdev, &rdev->rcfw,
					   BNXT_RE_MAX_QPC_COUNT);
	if (rc) {
		pr_err("Failed to allocate RCFW Channel: %#x\n", rc);
		goto fail;
	}
	rc = bnxt_re_net_ring_alloc
			(rdev, rdev->rcfw.creq.pbl[PBL_LVL_0].pg_map_arr,
			 rdev->rcfw.creq.pbl[rdev->rcfw.creq.level].pg_count,
			 HWRM_RING_ALLOC_CMPL, BNXT_QPLIB_CREQE_MAX_CNT - 1,
			 rdev->msix_entries[BNXT_RE_AEQ_IDX].ring_idx,
			 &rdev->rcfw.creq_ring_id);
	if (rc) {
		pr_err("Failed to allocate CREQ: %#x\n", rc);
		goto free_rcfw;
	}
	rc = bnxt_qplib_enable_rcfw_channel
				(rdev->en_dev->pdev, &rdev->rcfw,
				 rdev->msix_entries[BNXT_RE_AEQ_IDX].vector,
				 rdev->msix_entries[BNXT_RE_AEQ_IDX].db_offset,
				 rdev->is_virtfn, &bnxt_re_aeq_handler);
	if (rc) {
		pr_err("Failed to enable RCFW channel: %#x\n", rc);
		goto free_ring;
	}

	rc = bnxt_qplib_get_dev_attr(&rdev->rcfw, &rdev->dev_attr,
				     rdev->is_virtfn);
	if (rc)
		goto disable_rcfw;
	if (!rdev->is_virtfn)
		bnxt_re_set_resource_limits(rdev);

	rc = bnxt_qplib_alloc_ctx(rdev->en_dev->pdev, &rdev->qplib_ctx, 0);
	if (rc) {
		pr_err("Failed to allocate QPLIB context: %#x\n", rc);
		goto disable_rcfw;
	}
	rc = bnxt_re_net_stats_ctx_alloc(rdev,
					 rdev->qplib_ctx.stats.dma_map,
					 &rdev->qplib_ctx.stats.fw_id);
	if (rc) {
		pr_err("Failed to allocate stats context: %#x\n", rc);
		goto free_ctx;
	}

	rc = bnxt_qplib_init_rcfw(&rdev->rcfw, &rdev->qplib_ctx,
				  rdev->is_virtfn);
	if (rc) {
		pr_err("Failed to initialize RCFW: %#x\n", rc);
		goto free_sctx;
	}
	set_bit(BNXT_RE_FLAG_RCFW_CHANNEL_EN, &rdev->flags);

	/* Resources based on the 'new' device caps */
	rc = bnxt_re_alloc_res(rdev);
	if (rc) {
		pr_err("Failed to allocate resources: %#x\n", rc);
		goto fail;
	}
	rc = bnxt_re_init_res(rdev);
	if (rc) {
		pr_err("Failed to initialize resources: %#x\n", rc);
		goto fail;
	}

	if (!rdev->is_virtfn) {
		rc = bnxt_re_setup_qos(rdev);
		if (rc)
			pr_info("RoCE priority not yet configured\n");

		INIT_DELAYED_WORK(&rdev->worker, bnxt_re_worker);
		set_bit(BNXT_RE_FLAG_QOS_WORK_REG, &rdev->flags);
		schedule_delayed_work(&rdev->worker, msecs_to_jiffies(30000));
	}

	rtnl_unlock();
	locked = false;

	/* Register ib dev */
	rc = bnxt_re_register_ib(rdev);
	if (rc) {
		pr_err("Failed to register with IB: %#x\n", rc);
		goto fail;
	}
	set_bit(BNXT_RE_FLAG_IBDEV_REGISTERED, &rdev->flags);
	dev_info(rdev_to_dev(rdev), "Device registered successfully");
	for (i = 0; i < ARRAY_SIZE(bnxt_re_attributes); i++) {
		rc = device_create_file(&rdev->ibdev.dev,
					bnxt_re_attributes[i]);
		if (rc) {
			dev_err(rdev_to_dev(rdev),
				"Failed to create IB sysfs: %#x", rc);
			/* Must clean up all created device files */
			for (j = 0; j < i; j++)
				device_remove_file(&rdev->ibdev.dev,
						   bnxt_re_attributes[j]);
			bnxt_re_unregister_ib(rdev);
			goto fail;
		}
	}
	ib_get_eth_speed(&rdev->ibdev, 1, &rdev->active_speed,
			 &rdev->active_width);
	set_bit(BNXT_RE_FLAG_ISSUE_ROCE_STATS, &rdev->flags);
	bnxt_re_dispatch_event(&rdev->ibdev, NULL, 1, IB_EVENT_PORT_ACTIVE);
	bnxt_re_dispatch_event(&rdev->ibdev, NULL, 1, IB_EVENT_GID_CHANGE);

	return 0;
free_sctx:
	bnxt_re_net_stats_ctx_free(rdev, rdev->qplib_ctx.stats.fw_id);
free_ctx:
	bnxt_qplib_free_ctx(rdev->en_dev->pdev, &rdev->qplib_ctx);
disable_rcfw:
	bnxt_qplib_disable_rcfw_channel(&rdev->rcfw);
free_ring:
	bnxt_re_net_ring_free(rdev, rdev->rcfw.creq_ring_id);
free_rcfw:
	bnxt_qplib_free_rcfw_channel(&rdev->rcfw);
fail:
	if (!locked)
		rtnl_lock();
	bnxt_re_ib_unreg(rdev);
	rtnl_unlock();

	return rc;
}