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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mlxsw_res {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  in_mbox; int /*<<< orphan*/  out_mbox; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  subminor; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_5__ {int /*<<< orphan*/  device_kind; TYPE_1__ fw_rev; } ;
struct mlxsw_pci {TYPE_3__ cmd; TYPE_2__ bus_info; int /*<<< orphan*/  max_cqe_ver; int /*<<< orphan*/  free_running_clock_offset; int /*<<< orphan*/  doorbell_offset; int /*<<< orphan*/  id; struct mlxsw_core* core; struct pci_dev* pdev; } ;
struct mlxsw_core {int dummy; } ;
struct mlxsw_config_profile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQE_V0 ; 
 int /*<<< orphan*/  CQE_V1 ; 
 int /*<<< orphan*/  CQE_V2 ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ MLXSW_CORE_RES_GET (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLXSW_CORE_RES_VALID (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_PCI_CQE_V0 ; 
 int /*<<< orphan*/  MLXSW_PCI_CQE_V1 ; 
 int /*<<< orphan*/  MLXSW_PCI_CQE_V2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 char* mlxsw_cmd_mbox_alloc () ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_free (char*) ; 
 int mlxsw_cmd_mbox_query_fw_cmd_interface_rev_get (char*) ; 
 scalar_t__ mlxsw_cmd_mbox_query_fw_doorbell_page_bar_get (char*) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_query_fw_doorbell_page_offset_get (char*) ; 
 scalar_t__ mlxsw_cmd_mbox_query_fw_fr_rn_clk_bar_get (char*) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_query_fw_free_running_clock_offset_get (char*) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_query_fw_fw_pages_get (char*) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_query_fw_fw_rev_major_get (char*) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_query_fw_fw_rev_minor_get (char*) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_query_fw_fw_rev_subminor_get (char*) ; 
 int mlxsw_cmd_query_fw (struct mlxsw_core*,char*) ; 
 int mlxsw_core_resources_query (struct mlxsw_core*,char*,struct mlxsw_res*) ; 
 int mlxsw_pci_alloc_irq_vectors (struct mlxsw_pci*) ; 
 int /*<<< orphan*/  mlxsw_pci_aqs_fini (struct mlxsw_pci*) ; 
 int mlxsw_pci_aqs_init (struct mlxsw_pci*,char*) ; 
 int mlxsw_pci_boardinfo (struct mlxsw_pci*,char*) ; 
 int mlxsw_pci_config_profile (struct mlxsw_pci*,char*,struct mlxsw_config_profile const*,struct mlxsw_res*) ; 
 int /*<<< orphan*/  mlxsw_pci_eq_irq_handler ; 
 int /*<<< orphan*/  mlxsw_pci_free_irq_vectors (struct mlxsw_pci*) ; 
 int /*<<< orphan*/  mlxsw_pci_fw_area_fini (struct mlxsw_pci*) ; 
 int mlxsw_pci_fw_area_init (struct mlxsw_pci*,char*,int /*<<< orphan*/ ) ; 
 int mlxsw_pci_mbox_alloc (struct mlxsw_pci*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_pci_mbox_free (struct mlxsw_pci*,int /*<<< orphan*/ *) ; 
 int mlxsw_pci_sw_reset (struct mlxsw_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_pci*) ; 

__attribute__((used)) static int mlxsw_pci_init(void *bus_priv, struct mlxsw_core *mlxsw_core,
			  const struct mlxsw_config_profile *profile,
			  struct mlxsw_res *res)
{
	struct mlxsw_pci *mlxsw_pci = bus_priv;
	struct pci_dev *pdev = mlxsw_pci->pdev;
	char *mbox;
	u16 num_pages;
	int err;

	mutex_init(&mlxsw_pci->cmd.lock);
	init_waitqueue_head(&mlxsw_pci->cmd.wait);

	mlxsw_pci->core = mlxsw_core;

	mbox = mlxsw_cmd_mbox_alloc();
	if (!mbox)
		return -ENOMEM;

	err = mlxsw_pci_mbox_alloc(mlxsw_pci, &mlxsw_pci->cmd.in_mbox);
	if (err)
		goto mbox_put;

	err = mlxsw_pci_mbox_alloc(mlxsw_pci, &mlxsw_pci->cmd.out_mbox);
	if (err)
		goto err_out_mbox_alloc;

	err = mlxsw_pci_sw_reset(mlxsw_pci, mlxsw_pci->id);
	if (err)
		goto err_sw_reset;

	err = mlxsw_pci_alloc_irq_vectors(mlxsw_pci);
	if (err < 0) {
		dev_err(&pdev->dev, "MSI-X init failed\n");
		goto err_alloc_irq;
	}

	err = mlxsw_cmd_query_fw(mlxsw_core, mbox);
	if (err)
		goto err_query_fw;

	mlxsw_pci->bus_info.fw_rev.major =
		mlxsw_cmd_mbox_query_fw_fw_rev_major_get(mbox);
	mlxsw_pci->bus_info.fw_rev.minor =
		mlxsw_cmd_mbox_query_fw_fw_rev_minor_get(mbox);
	mlxsw_pci->bus_info.fw_rev.subminor =
		mlxsw_cmd_mbox_query_fw_fw_rev_subminor_get(mbox);

	if (mlxsw_cmd_mbox_query_fw_cmd_interface_rev_get(mbox) != 1) {
		dev_err(&pdev->dev, "Unsupported cmd interface revision ID queried from hw\n");
		err = -EINVAL;
		goto err_iface_rev;
	}
	if (mlxsw_cmd_mbox_query_fw_doorbell_page_bar_get(mbox) != 0) {
		dev_err(&pdev->dev, "Unsupported doorbell page bar queried from hw\n");
		err = -EINVAL;
		goto err_doorbell_page_bar;
	}

	mlxsw_pci->doorbell_offset =
		mlxsw_cmd_mbox_query_fw_doorbell_page_offset_get(mbox);

	if (mlxsw_cmd_mbox_query_fw_fr_rn_clk_bar_get(mbox) != 0) {
		dev_err(&pdev->dev, "Unsupported free running clock BAR queried from hw\n");
		err = -EINVAL;
		goto err_fr_rn_clk_bar;
	}

	mlxsw_pci->free_running_clock_offset =
		mlxsw_cmd_mbox_query_fw_free_running_clock_offset_get(mbox);

	num_pages = mlxsw_cmd_mbox_query_fw_fw_pages_get(mbox);
	err = mlxsw_pci_fw_area_init(mlxsw_pci, mbox, num_pages);
	if (err)
		goto err_fw_area_init;

	err = mlxsw_pci_boardinfo(mlxsw_pci, mbox);
	if (err)
		goto err_boardinfo;

	err = mlxsw_core_resources_query(mlxsw_core, mbox, res);
	if (err)
		goto err_query_resources;

	if (MLXSW_CORE_RES_VALID(mlxsw_core, CQE_V2) &&
	    MLXSW_CORE_RES_GET(mlxsw_core, CQE_V2))
		mlxsw_pci->max_cqe_ver = MLXSW_PCI_CQE_V2;
	else if (MLXSW_CORE_RES_VALID(mlxsw_core, CQE_V1) &&
		 MLXSW_CORE_RES_GET(mlxsw_core, CQE_V1))
		mlxsw_pci->max_cqe_ver = MLXSW_PCI_CQE_V1;
	else if ((MLXSW_CORE_RES_VALID(mlxsw_core, CQE_V0) &&
		  MLXSW_CORE_RES_GET(mlxsw_core, CQE_V0)) ||
		 !MLXSW_CORE_RES_VALID(mlxsw_core, CQE_V0)) {
		mlxsw_pci->max_cqe_ver = MLXSW_PCI_CQE_V0;
	} else {
		dev_err(&pdev->dev, "Invalid supported CQE version combination reported\n");
		goto err_cqe_v_check;
	}

	err = mlxsw_pci_config_profile(mlxsw_pci, mbox, profile, res);
	if (err)
		goto err_config_profile;

	err = mlxsw_pci_aqs_init(mlxsw_pci, mbox);
	if (err)
		goto err_aqs_init;

	err = request_irq(pci_irq_vector(pdev, 0),
			  mlxsw_pci_eq_irq_handler, 0,
			  mlxsw_pci->bus_info.device_kind, mlxsw_pci);
	if (err) {
		dev_err(&pdev->dev, "IRQ request failed\n");
		goto err_request_eq_irq;
	}

	goto mbox_put;

err_request_eq_irq:
	mlxsw_pci_aqs_fini(mlxsw_pci);
err_aqs_init:
err_config_profile:
err_cqe_v_check:
err_query_resources:
err_boardinfo:
	mlxsw_pci_fw_area_fini(mlxsw_pci);
err_fw_area_init:
err_fr_rn_clk_bar:
err_doorbell_page_bar:
err_iface_rev:
err_query_fw:
	mlxsw_pci_free_irq_vectors(mlxsw_pci);
err_alloc_irq:
err_sw_reset:
	mlxsw_pci_mbox_free(mlxsw_pci, &mlxsw_pci->cmd.out_mbox);
err_out_mbox_alloc:
	mlxsw_pci_mbox_free(mlxsw_pci, &mlxsw_pci->cmd.in_mbox);
mbox_put:
	mlxsw_cmd_mbox_free(mbox);
	return err;
}