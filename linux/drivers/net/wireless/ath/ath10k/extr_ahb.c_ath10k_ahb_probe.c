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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bus_ops; } ;
struct ath10k_pci {TYPE_1__ ce; int /*<<< orphan*/  targ_cpu_to_ce_addr; struct ath10k* ar; int /*<<< orphan*/  mem_len; int /*<<< orphan*/  mem; } ;
struct ath10k_bus_params {int chip_id; int /*<<< orphan*/  dev_type; } ;
struct ath10k_ahb {int /*<<< orphan*/  mem_len; int /*<<< orphan*/  mem; struct platform_device* pdev; } ;
struct ath10k {TYPE_1__* ce_priv; scalar_t__ dev_id; } ;
typedef  enum ath10k_hw_rev { ____Placeholder_ath10k_hw_rev } ath10k_hw_rev ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_BUS_AHB ; 
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ATH10K_DEV_TYPE_LL ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SOC_CHIP_ID_ADDRESS ; 
 int /*<<< orphan*/  ath10k_ahb_bus_ops ; 
 int /*<<< orphan*/  ath10k_ahb_clock_disable (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_ahb_halt_chip (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_ahb_hif_ops ; 
 int /*<<< orphan*/  ath10k_ahb_of_match ; 
 int ath10k_ahb_prepare_device (struct ath10k*) ; 
 struct ath10k_ahb* ath10k_ahb_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_ahb_qca4019_targ_cpu_to_ce_addr ; 
 int /*<<< orphan*/  ath10k_ahb_release_irq_legacy (struct ath10k*) ; 
 int ath10k_ahb_request_irq_legacy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_ahb_resource_deinit (struct ath10k*) ; 
 int ath10k_ahb_resource_init (struct ath10k*) ; 
 int ath10k_ahb_soc_read32 (struct ath10k*,int /*<<< orphan*/ ) ; 
 struct ath10k* ath10k_core_create (size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_core_destroy (struct ath10k*) ; 
 int ath10k_core_register (struct ath10k*,struct ath10k_bus_params*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,...) ; 
 int /*<<< orphan*/  ath10k_pci_ce_deinit (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_free_pipes (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_init_napi (struct ath10k*) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int ath10k_pci_setup_resource (struct ath10k*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ath10k*) ; 

__attribute__((used)) static int ath10k_ahb_probe(struct platform_device *pdev)
{
	struct ath10k *ar;
	struct ath10k_ahb *ar_ahb;
	struct ath10k_pci *ar_pci;
	const struct of_device_id *of_id;
	enum ath10k_hw_rev hw_rev;
	size_t size;
	int ret;
	struct ath10k_bus_params bus_params = {};

	of_id = of_match_device(ath10k_ahb_of_match, &pdev->dev);
	if (!of_id) {
		dev_err(&pdev->dev, "failed to find matching device tree id\n");
		return -EINVAL;
	}

	hw_rev = (enum ath10k_hw_rev)of_id->data;

	size = sizeof(*ar_pci) + sizeof(*ar_ahb);
	ar = ath10k_core_create(size, &pdev->dev, ATH10K_BUS_AHB,
				hw_rev, &ath10k_ahb_hif_ops);
	if (!ar) {
		dev_err(&pdev->dev, "failed to allocate core\n");
		return -ENOMEM;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "ahb probe\n");

	ar_pci = ath10k_pci_priv(ar);
	ar_ahb = ath10k_ahb_priv(ar);

	ar_ahb->pdev = pdev;
	platform_set_drvdata(pdev, ar);

	ret = ath10k_ahb_resource_init(ar);
	if (ret)
		goto err_core_destroy;

	ar->dev_id = 0;
	ar_pci->mem = ar_ahb->mem;
	ar_pci->mem_len = ar_ahb->mem_len;
	ar_pci->ar = ar;
	ar_pci->ce.bus_ops = &ath10k_ahb_bus_ops;
	ar_pci->targ_cpu_to_ce_addr = ath10k_ahb_qca4019_targ_cpu_to_ce_addr;
	ar->ce_priv = &ar_pci->ce;

	ret = ath10k_pci_setup_resource(ar);
	if (ret) {
		ath10k_err(ar, "failed to setup resource: %d\n", ret);
		goto err_resource_deinit;
	}

	ath10k_pci_init_napi(ar);

	ret = ath10k_ahb_request_irq_legacy(ar);
	if (ret)
		goto err_free_pipes;

	ret = ath10k_ahb_prepare_device(ar);
	if (ret)
		goto err_free_irq;

	ath10k_pci_ce_deinit(ar);

	bus_params.dev_type = ATH10K_DEV_TYPE_LL;
	bus_params.chip_id = ath10k_ahb_soc_read32(ar, SOC_CHIP_ID_ADDRESS);
	if (bus_params.chip_id == 0xffffffff) {
		ath10k_err(ar, "failed to get chip id\n");
		ret = -ENODEV;
		goto err_halt_device;
	}

	ret = ath10k_core_register(ar, &bus_params);
	if (ret) {
		ath10k_err(ar, "failed to register driver core: %d\n", ret);
		goto err_halt_device;
	}

	return 0;

err_halt_device:
	ath10k_ahb_halt_chip(ar);
	ath10k_ahb_clock_disable(ar);

err_free_irq:
	ath10k_ahb_release_irq_legacy(ar);

err_free_pipes:
	ath10k_pci_free_pipes(ar);

err_resource_deinit:
	ath10k_ahb_resource_deinit(ar);

err_core_destroy:
	ath10k_core_destroy(ar);
	platform_set_drvdata(pdev, NULL);

	return ret;
}