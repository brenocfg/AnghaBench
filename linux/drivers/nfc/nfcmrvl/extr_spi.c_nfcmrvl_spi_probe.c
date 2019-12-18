#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ of_node; struct nfcmrvl_platform_data* platform_data; } ;
struct spi_device {TYPE_2__ dev; } ;
struct nfcmrvl_spi_drv_data {int /*<<< orphan*/  handshake_completion; TYPE_1__* priv; struct spi_device* spi; int /*<<< orphan*/  nci_spi; } ;
struct nfcmrvl_platform_data {int /*<<< orphan*/  irq; } ;
struct TYPE_8__ {int support_fw_dnld; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  NFCMRVL_PHY_SPI ; 
 int PTR_ERR (TYPE_1__*) ; 
 struct nfcmrvl_spi_drv_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct nfcmrvl_spi_drv_data*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nci_spi_allocate_spi (struct spi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_err (TYPE_2__*,char*) ; 
 TYPE_1__* nfcmrvl_nci_register_dev (int /*<<< orphan*/ ,struct nfcmrvl_spi_drv_data*,int /*<<< orphan*/ *,TYPE_2__*,struct nfcmrvl_platform_data*) ; 
 int /*<<< orphan*/  nfcmrvl_spi_int_irq_thread_fn ; 
 scalar_t__ nfcmrvl_spi_parse_dt (scalar_t__,struct nfcmrvl_platform_data*) ; 
 int /*<<< orphan*/  spi_ops ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct nfcmrvl_spi_drv_data*) ; 

__attribute__((used)) static int nfcmrvl_spi_probe(struct spi_device *spi)
{
	struct nfcmrvl_platform_data *pdata;
	struct nfcmrvl_platform_data config;
	struct nfcmrvl_spi_drv_data *drv_data;
	int ret = 0;

	drv_data = devm_kzalloc(&spi->dev, sizeof(*drv_data), GFP_KERNEL);
	if (!drv_data)
		return -ENOMEM;

	drv_data->spi = spi;
	drv_data->priv = NULL;
	spi_set_drvdata(spi, drv_data);

	pdata = spi->dev.platform_data;

	if (!pdata && spi->dev.of_node)
		if (nfcmrvl_spi_parse_dt(spi->dev.of_node, &config) == 0)
			pdata = &config;

	if (!pdata)
		return -EINVAL;

	ret = devm_request_threaded_irq(&drv_data->spi->dev, pdata->irq,
					NULL, nfcmrvl_spi_int_irq_thread_fn,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					"nfcmrvl_spi_int", drv_data);
	if (ret < 0) {
		nfc_err(&drv_data->spi->dev, "Unable to register IRQ handler");
		return -ENODEV;
	}

	drv_data->priv = nfcmrvl_nci_register_dev(NFCMRVL_PHY_SPI,
						  drv_data, &spi_ops,
						  &drv_data->spi->dev,
						  pdata);
	if (IS_ERR(drv_data->priv))
		return PTR_ERR(drv_data->priv);

	drv_data->priv->support_fw_dnld = true;

	drv_data->nci_spi = nci_spi_allocate_spi(drv_data->spi, 0, 10,
						 drv_data->priv->ndev);

	/* Init completion for slave handshake */
	init_completion(&drv_data->handshake_completion);
	return 0;
}