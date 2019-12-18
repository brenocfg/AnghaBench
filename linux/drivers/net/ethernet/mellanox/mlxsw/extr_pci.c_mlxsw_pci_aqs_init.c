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
typedef  scalar_t__ u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int nopoll; } ;
struct mlxsw_pci {scalar_t__ max_cqe_ver; TYPE_1__ cmd; scalar_t__ num_sdq_cqs; int /*<<< orphan*/  core; struct pci_dev* pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLXSW_PCI_CQE01_COUNT ; 
 scalar_t__ MLXSW_PCI_CQE2_COUNT ; 
 scalar_t__ MLXSW_PCI_CQE_V2 ; 
 scalar_t__ MLXSW_PCI_CQS_MAX ; 
 scalar_t__ MLXSW_PCI_EQE_COUNT ; 
 scalar_t__ MLXSW_PCI_EQS_COUNT ; 
 scalar_t__ MLXSW_PCI_WQE_COUNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mlxsw_cmd_mbox_query_aq_cap_log_max_cq_sz_get (char*) ; 
 scalar_t__ mlxsw_cmd_mbox_query_aq_cap_log_max_cqv2_sz_get (char*) ; 
 scalar_t__ mlxsw_cmd_mbox_query_aq_cap_log_max_eq_sz_get (char*) ; 
 scalar_t__ mlxsw_cmd_mbox_query_aq_cap_log_max_rdq_sz_get (char*) ; 
 scalar_t__ mlxsw_cmd_mbox_query_aq_cap_log_max_sdq_sz_get (char*) ; 
 scalar_t__ mlxsw_cmd_mbox_query_aq_cap_max_num_cqs_get (char*) ; 
 scalar_t__ mlxsw_cmd_mbox_query_aq_cap_max_num_eqs_get (char*) ; 
 scalar_t__ mlxsw_cmd_mbox_query_aq_cap_max_num_rdqs_get (char*) ; 
 scalar_t__ mlxsw_cmd_mbox_query_aq_cap_max_num_sdqs_get (char*) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_zero (char*) ; 
 int mlxsw_cmd_query_aq_cap (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_pci_cq_ops ; 
 int /*<<< orphan*/  mlxsw_pci_eq_ops ; 
 int /*<<< orphan*/  mlxsw_pci_queue_group_fini (struct mlxsw_pci*,int /*<<< orphan*/ *) ; 
 int mlxsw_pci_queue_group_init (struct mlxsw_pci*,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_pci_rdq_ops ; 
 int /*<<< orphan*/  mlxsw_pci_sdq_ops ; 

__attribute__((used)) static int mlxsw_pci_aqs_init(struct mlxsw_pci *mlxsw_pci, char *mbox)
{
	struct pci_dev *pdev = mlxsw_pci->pdev;
	u8 num_sdqs;
	u8 sdq_log2sz;
	u8 num_rdqs;
	u8 rdq_log2sz;
	u8 num_cqs;
	u8 cq_log2sz;
	u8 cqv2_log2sz;
	u8 num_eqs;
	u8 eq_log2sz;
	int err;

	mlxsw_cmd_mbox_zero(mbox);
	err = mlxsw_cmd_query_aq_cap(mlxsw_pci->core, mbox);
	if (err)
		return err;

	num_sdqs = mlxsw_cmd_mbox_query_aq_cap_max_num_sdqs_get(mbox);
	sdq_log2sz = mlxsw_cmd_mbox_query_aq_cap_log_max_sdq_sz_get(mbox);
	num_rdqs = mlxsw_cmd_mbox_query_aq_cap_max_num_rdqs_get(mbox);
	rdq_log2sz = mlxsw_cmd_mbox_query_aq_cap_log_max_rdq_sz_get(mbox);
	num_cqs = mlxsw_cmd_mbox_query_aq_cap_max_num_cqs_get(mbox);
	cq_log2sz = mlxsw_cmd_mbox_query_aq_cap_log_max_cq_sz_get(mbox);
	cqv2_log2sz = mlxsw_cmd_mbox_query_aq_cap_log_max_cqv2_sz_get(mbox);
	num_eqs = mlxsw_cmd_mbox_query_aq_cap_max_num_eqs_get(mbox);
	eq_log2sz = mlxsw_cmd_mbox_query_aq_cap_log_max_eq_sz_get(mbox);

	if (num_sdqs + num_rdqs > num_cqs ||
	    num_cqs > MLXSW_PCI_CQS_MAX || num_eqs != MLXSW_PCI_EQS_COUNT) {
		dev_err(&pdev->dev, "Unsupported number of queues\n");
		return -EINVAL;
	}

	if ((1 << sdq_log2sz != MLXSW_PCI_WQE_COUNT) ||
	    (1 << rdq_log2sz != MLXSW_PCI_WQE_COUNT) ||
	    (1 << cq_log2sz != MLXSW_PCI_CQE01_COUNT) ||
	    (mlxsw_pci->max_cqe_ver == MLXSW_PCI_CQE_V2 &&
	     (1 << cqv2_log2sz != MLXSW_PCI_CQE2_COUNT)) ||
	    (1 << eq_log2sz != MLXSW_PCI_EQE_COUNT)) {
		dev_err(&pdev->dev, "Unsupported number of async queue descriptors\n");
		return -EINVAL;
	}

	mlxsw_pci->num_sdq_cqs = num_sdqs;

	err = mlxsw_pci_queue_group_init(mlxsw_pci, mbox, &mlxsw_pci_eq_ops,
					 num_eqs);
	if (err) {
		dev_err(&pdev->dev, "Failed to initialize event queues\n");
		return err;
	}

	err = mlxsw_pci_queue_group_init(mlxsw_pci, mbox, &mlxsw_pci_cq_ops,
					 num_cqs);
	if (err) {
		dev_err(&pdev->dev, "Failed to initialize completion queues\n");
		goto err_cqs_init;
	}

	err = mlxsw_pci_queue_group_init(mlxsw_pci, mbox, &mlxsw_pci_sdq_ops,
					 num_sdqs);
	if (err) {
		dev_err(&pdev->dev, "Failed to initialize send descriptor queues\n");
		goto err_sdqs_init;
	}

	err = mlxsw_pci_queue_group_init(mlxsw_pci, mbox, &mlxsw_pci_rdq_ops,
					 num_rdqs);
	if (err) {
		dev_err(&pdev->dev, "Failed to initialize receive descriptor queues\n");
		goto err_rdqs_init;
	}

	/* We have to poll in command interface until queues are initialized */
	mlxsw_pci->cmd.nopoll = true;
	return 0;

err_rdqs_init:
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_sdq_ops);
err_sdqs_init:
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_cq_ops);
err_cqs_init:
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_eq_ops);
	return err;
}