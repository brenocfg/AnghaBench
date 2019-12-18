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
typedef  size_t u32 ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {struct ath10k_snoc_drv_priv* data; } ;
struct ath10k_snoc_drv_priv {size_t msa_size; int /*<<< orphan*/  hw_rev; int /*<<< orphan*/  dma_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bus_ops; } ;
struct ath10k_snoc {int /*<<< orphan*/ * clk; int /*<<< orphan*/ * vreg; TYPE_1__ ce; struct ath10k* ar; struct platform_device* dev; } ;
struct ath10k {TYPE_1__* ce_priv; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  ATH10K_BUS_SNOC ; 
 int /*<<< orphan*/  ATH10K_DBG_SNOC ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ath10k* ath10k_core_create (int,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_core_destroy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int ath10k_get_clk_info (struct ath10k*,struct device*,int /*<<< orphan*/ *) ; 
 int ath10k_get_vreg_info (struct ath10k*,struct device*,int /*<<< orphan*/ *) ; 
 int ath10k_hw_power_on (struct ath10k*) ; 
 int ath10k_qmi_init (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ath10k_snoc_bus_ops ; 
 int /*<<< orphan*/  ath10k_snoc_dt_match ; 
 int /*<<< orphan*/  ath10k_snoc_free_irq (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_snoc_hif_ops ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_snoc_release_resource (struct ath10k*) ; 
 int ath10k_snoc_request_irq (struct ath10k*) ; 
 int ath10k_snoc_resource_init (struct ath10k*) ; 
 int ath10k_snoc_setup_resource (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 void* clk_cfg ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ath10k*) ; 
 void* vreg_cfg ; 

__attribute__((used)) static int ath10k_snoc_probe(struct platform_device *pdev)
{
	const struct ath10k_snoc_drv_priv *drv_data;
	const struct of_device_id *of_id;
	struct ath10k_snoc *ar_snoc;
	struct device *dev;
	struct ath10k *ar;
	u32 msa_size;
	int ret;
	u32 i;

	of_id = of_match_device(ath10k_snoc_dt_match, &pdev->dev);
	if (!of_id) {
		dev_err(&pdev->dev, "failed to find matching device tree id\n");
		return -EINVAL;
	}

	drv_data = of_id->data;
	dev = &pdev->dev;

	ret = dma_set_mask_and_coherent(dev, drv_data->dma_mask);
	if (ret) {
		dev_err(dev, "failed to set dma mask: %d", ret);
		return ret;
	}

	ar = ath10k_core_create(sizeof(*ar_snoc), dev, ATH10K_BUS_SNOC,
				drv_data->hw_rev, &ath10k_snoc_hif_ops);
	if (!ar) {
		dev_err(dev, "failed to allocate core\n");
		return -ENOMEM;
	}

	ar_snoc = ath10k_snoc_priv(ar);
	ar_snoc->dev = pdev;
	platform_set_drvdata(pdev, ar);
	ar_snoc->ar = ar;
	ar_snoc->ce.bus_ops = &ath10k_snoc_bus_ops;
	ar->ce_priv = &ar_snoc->ce;
	msa_size = drv_data->msa_size;

	ret = ath10k_snoc_resource_init(ar);
	if (ret) {
		ath10k_warn(ar, "failed to initialize resource: %d\n", ret);
		goto err_core_destroy;
	}

	ret = ath10k_snoc_setup_resource(ar);
	if (ret) {
		ath10k_warn(ar, "failed to setup resource: %d\n", ret);
		goto err_core_destroy;
	}
	ret = ath10k_snoc_request_irq(ar);
	if (ret) {
		ath10k_warn(ar, "failed to request irqs: %d\n", ret);
		goto err_release_resource;
	}

	ar_snoc->vreg = vreg_cfg;
	for (i = 0; i < ARRAY_SIZE(vreg_cfg); i++) {
		ret = ath10k_get_vreg_info(ar, dev, &ar_snoc->vreg[i]);
		if (ret)
			goto err_free_irq;
	}

	ar_snoc->clk = clk_cfg;
	for (i = 0; i < ARRAY_SIZE(clk_cfg); i++) {
		ret = ath10k_get_clk_info(ar, dev, &ar_snoc->clk[i]);
		if (ret)
			goto err_free_irq;
	}

	ret = ath10k_hw_power_on(ar);
	if (ret) {
		ath10k_err(ar, "failed to power on device: %d\n", ret);
		goto err_free_irq;
	}

	ret = ath10k_qmi_init(ar, msa_size);
	if (ret) {
		ath10k_warn(ar, "failed to register wlfw qmi client: %d\n", ret);
		goto err_core_destroy;
	}

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc probe\n");

	return 0;

err_free_irq:
	ath10k_snoc_free_irq(ar);

err_release_resource:
	ath10k_snoc_release_resource(ar);

err_core_destroy:
	ath10k_core_destroy(ar);

	return ret;
}