#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u32 ;
struct mlx4_init_hca_param {int log_rd_per_qp; scalar_t__ uar_page_sz; unsigned long long pf_context_behaviour; unsigned long long num_ports; int log_num_qps; int log_num_srqs; int log_num_cqs; int log_mpt_sz; int dev_cap_enabled; int eqe_size; int cqe_size; int extra_flags; scalar_t__ rss_ip_frags; int /*<<< orphan*/  reserved_lkey; int /*<<< orphan*/  reserved_eq; int /*<<< orphan*/  max_eq; int /*<<< orphan*/  mtt_quota; int /*<<< orphan*/  mpt_quota; int /*<<< orphan*/  cq_quota; int /*<<< orphan*/  srq_quota; int /*<<< orphan*/  qp_quota; int /*<<< orphan*/  hca_core_clock; scalar_t__ global_caps; } ;
struct mlx4_func_cap {int log_rd_per_qp; scalar_t__ uar_page_sz; unsigned long long pf_context_behaviour; unsigned long long num_ports; int log_num_qps; int log_num_srqs; int log_num_cqs; int log_mpt_sz; int dev_cap_enabled; int eqe_size; int cqe_size; int extra_flags; scalar_t__ rss_ip_frags; int /*<<< orphan*/  reserved_lkey; int /*<<< orphan*/  reserved_eq; int /*<<< orphan*/  max_eq; int /*<<< orphan*/  mtt_quota; int /*<<< orphan*/  mpt_quota; int /*<<< orphan*/  cq_quota; int /*<<< orphan*/  srq_quota; int /*<<< orphan*/  qp_quota; int /*<<< orphan*/  hca_core_clock; scalar_t__ global_caps; } ;
struct mlx4_dev_cap {int log_rd_per_qp; scalar_t__ uar_page_sz; unsigned long long pf_context_behaviour; unsigned long long num_ports; int log_num_qps; int log_num_srqs; int log_num_cqs; int log_mpt_sz; int dev_cap_enabled; int eqe_size; int cqe_size; int extra_flags; scalar_t__ rss_ip_frags; int /*<<< orphan*/  reserved_lkey; int /*<<< orphan*/  reserved_eq; int /*<<< orphan*/  max_eq; int /*<<< orphan*/  mtt_quota; int /*<<< orphan*/  mpt_quota; int /*<<< orphan*/  cq_quota; int /*<<< orphan*/  srq_quota; int /*<<< orphan*/  qp_quota; int /*<<< orphan*/  hca_core_clock; scalar_t__ global_caps; } ;
struct TYPE_6__ {int max_qp_dest_rdma; int page_size_cap; unsigned long long uar_page_size; unsigned long long num_ports; int num_qps; int num_srqs; int num_cqs; int num_mpts; unsigned long long num_uars; int reserved_uars; int eqe_size; int eqe_factor; int cqe_size; int /*<<< orphan*/  alloc_res_qp_mask; scalar_t__ bf_reg_size; int /*<<< orphan*/  flags2; int /*<<< orphan*/  userspace_caps; scalar_t__ num_amgms; scalar_t__ num_mgms; int /*<<< orphan*/  num_pds; int /*<<< orphan*/  reserved_lkey; int /*<<< orphan*/  reserved_eqs; int /*<<< orphan*/  num_eqs; int /*<<< orphan*/  hca_core_clock; } ;
struct TYPE_5__ {int /*<<< orphan*/  mtt; int /*<<< orphan*/  mpt; int /*<<< orphan*/  cq; int /*<<< orphan*/  srq; int /*<<< orphan*/  qp; } ;
struct mlx4_dev {scalar_t__ uar_page_shift; TYPE_3__ caps; TYPE_1__* persist; TYPE_2__ quotas; } ;
struct TYPE_4__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX4_DEV_CAP_64B_CQE_ENABLED ; 
 int MLX4_DEV_CAP_64B_EQE_ENABLED ; 
 int MLX4_DEV_CAP_CQE_STRIDE_ENABLED ; 
 int MLX4_DEV_CAP_EQE_STRIDE_ENABLED ; 
 int /*<<< orphan*/  MLX4_DEV_CAP_FLAG2_TS ; 
 int /*<<< orphan*/  MLX4_DEV_CAP_FLAG2_USER_MAC_EN ; 
 unsigned long long MLX4_MAX_PORTS ; 
 int /*<<< orphan*/  MLX4_NUM_PDS ; 
 int MLX4_QUERY_FUNC_FLAGS_A0_RES_QP ; 
 int MLX4_QUERY_FUNC_FLAGS_BF_RES_QP ; 
 int /*<<< orphan*/  MLX4_RESERVE_A0_QP ; 
 int /*<<< orphan*/  MLX4_RESERVE_ETH_BF_QP ; 
 int /*<<< orphan*/  MLX4_USER_DEV_CAP_LARGE_CQE ; 
 scalar_t__ PAGE_SHIFT ; 
 unsigned long long PAGE_SIZE ; 
 unsigned long long PF_CONTEXT_BEHAVIOUR_MASK ; 
 int /*<<< orphan*/  kfree (struct mlx4_init_hca_param*) ; 
 struct mlx4_init_hca_param* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_QUERY_FUNC_CAP (struct mlx4_dev*,int /*<<< orphan*/ ,struct mlx4_init_hca_param*) ; 
 int mlx4_QUERY_FW (struct mlx4_dev*) ; 
 int mlx4_QUERY_HCA (struct mlx4_dev*,struct mlx4_init_hca_param*) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,...) ; 
 int mlx4_dev_cap (struct mlx4_dev*,struct mlx4_init_hca_param*) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx4_replace_zero_macs (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_set_num_reserved_uars (struct mlx4_dev*,struct mlx4_init_hca_param*) ; 
 int /*<<< orphan*/  mlx4_slave_destroy_special_qp_cap (struct mlx4_dev*) ; 
 int mlx4_slave_special_qp_cap (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,...) ; 
 int pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  slave_adjust_steering_mode (struct mlx4_dev*,struct mlx4_init_hca_param*,struct mlx4_init_hca_param*) ; 

__attribute__((used)) static int mlx4_slave_cap(struct mlx4_dev *dev)
{
	int			   err;
	u32			   page_size;
	struct mlx4_dev_cap	   *dev_cap = NULL;
	struct mlx4_func_cap	   *func_cap = NULL;
	struct mlx4_init_hca_param *hca_param = NULL;

	hca_param = kzalloc(sizeof(*hca_param), GFP_KERNEL);
	func_cap = kzalloc(sizeof(*func_cap), GFP_KERNEL);
	dev_cap = kzalloc(sizeof(*dev_cap), GFP_KERNEL);
	if (!hca_param || !func_cap || !dev_cap) {
		mlx4_err(dev, "Failed to allocate memory for slave_cap\n");
		err = -ENOMEM;
		goto free_mem;
	}

	err = mlx4_QUERY_HCA(dev, hca_param);
	if (err) {
		mlx4_err(dev, "QUERY_HCA command failed, aborting\n");
		goto free_mem;
	}

	/* fail if the hca has an unknown global capability
	 * at this time global_caps should be always zeroed
	 */
	if (hca_param->global_caps) {
		mlx4_err(dev, "Unknown hca global capabilities\n");
		err = -EINVAL;
		goto free_mem;
	}

	dev->caps.hca_core_clock = hca_param->hca_core_clock;

	dev->caps.max_qp_dest_rdma = 1 << hca_param->log_rd_per_qp;
	err = mlx4_dev_cap(dev, dev_cap);
	if (err) {
		mlx4_err(dev, "QUERY_DEV_CAP command failed, aborting\n");
		goto free_mem;
	}

	err = mlx4_QUERY_FW(dev);
	if (err)
		mlx4_err(dev, "QUERY_FW command failed: could not get FW version\n");

	page_size = ~dev->caps.page_size_cap + 1;
	mlx4_warn(dev, "HCA minimum page size:%d\n", page_size);
	if (page_size > PAGE_SIZE) {
		mlx4_err(dev, "HCA minimum page size of %d bigger than kernel PAGE_SIZE of %ld, aborting\n",
			 page_size, PAGE_SIZE);
		err = -ENODEV;
		goto free_mem;
	}

	/* Set uar_page_shift for VF */
	dev->uar_page_shift = hca_param->uar_page_sz + 12;

	/* Make sure the master uar page size is valid */
	if (dev->uar_page_shift > PAGE_SHIFT) {
		mlx4_err(dev,
			 "Invalid configuration: uar page size is larger than system page size\n");
		err = -ENODEV;
		goto free_mem;
	}

	/* Set reserved_uars based on the uar_page_shift */
	mlx4_set_num_reserved_uars(dev, dev_cap);

	/* Although uar page size in FW differs from system page size,
	 * upper software layers (mlx4_ib, mlx4_en and part of mlx4_core)
	 * still works with assumption that uar page size == system page size
	 */
	dev->caps.uar_page_size = PAGE_SIZE;

	err = mlx4_QUERY_FUNC_CAP(dev, 0, func_cap);
	if (err) {
		mlx4_err(dev, "QUERY_FUNC_CAP general command failed, aborting (%d)\n",
			 err);
		goto free_mem;
	}

	if ((func_cap->pf_context_behaviour | PF_CONTEXT_BEHAVIOUR_MASK) !=
	    PF_CONTEXT_BEHAVIOUR_MASK) {
		mlx4_err(dev, "Unknown pf context behaviour %x known flags %x\n",
			 func_cap->pf_context_behaviour,
			 PF_CONTEXT_BEHAVIOUR_MASK);
		err = -EINVAL;
		goto free_mem;
	}

	dev->caps.num_ports		= func_cap->num_ports;
	dev->quotas.qp			= func_cap->qp_quota;
	dev->quotas.srq			= func_cap->srq_quota;
	dev->quotas.cq			= func_cap->cq_quota;
	dev->quotas.mpt			= func_cap->mpt_quota;
	dev->quotas.mtt			= func_cap->mtt_quota;
	dev->caps.num_qps		= 1 << hca_param->log_num_qps;
	dev->caps.num_srqs		= 1 << hca_param->log_num_srqs;
	dev->caps.num_cqs		= 1 << hca_param->log_num_cqs;
	dev->caps.num_mpts		= 1 << hca_param->log_mpt_sz;
	dev->caps.num_eqs		= func_cap->max_eq;
	dev->caps.reserved_eqs		= func_cap->reserved_eq;
	dev->caps.reserved_lkey		= func_cap->reserved_lkey;
	dev->caps.num_pds               = MLX4_NUM_PDS;
	dev->caps.num_mgms              = 0;
	dev->caps.num_amgms             = 0;

	if (dev->caps.num_ports > MLX4_MAX_PORTS) {
		mlx4_err(dev, "HCA has %d ports, but we only support %d, aborting\n",
			 dev->caps.num_ports, MLX4_MAX_PORTS);
		err = -ENODEV;
		goto free_mem;
	}

	mlx4_replace_zero_macs(dev);

	err = mlx4_slave_special_qp_cap(dev);
	if (err) {
		mlx4_err(dev, "Set special QP caps failed. aborting\n");
		goto free_mem;
	}

	if (dev->caps.uar_page_size * (dev->caps.num_uars -
				       dev->caps.reserved_uars) >
				       pci_resource_len(dev->persist->pdev,
							2)) {
		mlx4_err(dev, "HCA reported UAR region size of 0x%x bigger than PCI resource 2 size of 0x%llx, aborting\n",
			 dev->caps.uar_page_size * dev->caps.num_uars,
			 (unsigned long long)
			 pci_resource_len(dev->persist->pdev, 2));
		err = -ENOMEM;
		goto err_mem;
	}

	if (hca_param->dev_cap_enabled & MLX4_DEV_CAP_64B_EQE_ENABLED) {
		dev->caps.eqe_size   = 64;
		dev->caps.eqe_factor = 1;
	} else {
		dev->caps.eqe_size   = 32;
		dev->caps.eqe_factor = 0;
	}

	if (hca_param->dev_cap_enabled & MLX4_DEV_CAP_64B_CQE_ENABLED) {
		dev->caps.cqe_size   = 64;
		dev->caps.userspace_caps |= MLX4_USER_DEV_CAP_LARGE_CQE;
	} else {
		dev->caps.cqe_size   = 32;
	}

	if (hca_param->dev_cap_enabled & MLX4_DEV_CAP_EQE_STRIDE_ENABLED) {
		dev->caps.eqe_size = hca_param->eqe_size;
		dev->caps.eqe_factor = 0;
	}

	if (hca_param->dev_cap_enabled & MLX4_DEV_CAP_CQE_STRIDE_ENABLED) {
		dev->caps.cqe_size = hca_param->cqe_size;
		/* User still need to know when CQE > 32B */
		dev->caps.userspace_caps |= MLX4_USER_DEV_CAP_LARGE_CQE;
	}

	dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_TS;
	mlx4_warn(dev, "Timestamping is not supported in slave mode\n");

	dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_USER_MAC_EN;
	mlx4_dbg(dev, "User MAC FW update is not supported in slave mode\n");

	slave_adjust_steering_mode(dev, dev_cap, hca_param);
	mlx4_dbg(dev, "RSS support for IP fragments is %s\n",
		 hca_param->rss_ip_frags ? "on" : "off");

	if (func_cap->extra_flags & MLX4_QUERY_FUNC_FLAGS_BF_RES_QP &&
	    dev->caps.bf_reg_size)
		dev->caps.alloc_res_qp_mask |= MLX4_RESERVE_ETH_BF_QP;

	if (func_cap->extra_flags & MLX4_QUERY_FUNC_FLAGS_A0_RES_QP)
		dev->caps.alloc_res_qp_mask |= MLX4_RESERVE_A0_QP;

err_mem:
	if (err)
		mlx4_slave_destroy_special_qp_cap(dev);
free_mem:
	kfree(hca_param);
	kfree(func_cap);
	kfree(dev_cap);
	return err;
}