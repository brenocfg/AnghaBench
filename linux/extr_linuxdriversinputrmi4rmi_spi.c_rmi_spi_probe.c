#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ of_node; struct rmi_device_platform_data* platform_data; } ;
struct spi_device {TYPE_4__ dev; int /*<<< orphan*/  irq; scalar_t__ mode; scalar_t__ bits_per_word; TYPE_1__* master; } ;
struct TYPE_9__ {scalar_t__ mode; scalar_t__ bits_per_word; } ;
struct rmi_device_platform_data {int /*<<< orphan*/  irq; TYPE_2__ spi_data; } ;
struct TYPE_10__ {char* proto_name; int /*<<< orphan*/ * ops; TYPE_4__* dev; struct rmi_device_platform_data pdata; } ;
struct rmi_spi_xport {TYPE_3__ xport; int /*<<< orphan*/  page_mutex; struct spi_device* spi; } ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RMI_SPI_DEFAULT_XFER_BUF_SIZE ; 
 int SPI_MASTER_HALF_DUPLEX ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*) ; 
 int devm_add_action_or_reset (TYPE_4__*,int /*<<< orphan*/ ,struct rmi_spi_xport*) ; 
 struct rmi_spi_xport* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int rmi_register_transport_device (TYPE_3__*) ; 
 int rmi_set_page (struct rmi_spi_xport*,int /*<<< orphan*/ ) ; 
 int rmi_spi_manage_pools (struct rmi_spi_xport*,int /*<<< orphan*/ ) ; 
 int rmi_spi_of_probe (struct spi_device*,struct rmi_device_platform_data*) ; 
 int /*<<< orphan*/  rmi_spi_ops ; 
 int /*<<< orphan*/  rmi_spi_unregister_transport ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct rmi_spi_xport*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int rmi_spi_probe(struct spi_device *spi)
{
	struct rmi_spi_xport *rmi_spi;
	struct rmi_device_platform_data *pdata;
	struct rmi_device_platform_data *spi_pdata = spi->dev.platform_data;
	int error;

	if (spi->master->flags & SPI_MASTER_HALF_DUPLEX)
		return -EINVAL;

	rmi_spi = devm_kzalloc(&spi->dev, sizeof(struct rmi_spi_xport),
			GFP_KERNEL);
	if (!rmi_spi)
		return -ENOMEM;

	pdata = &rmi_spi->xport.pdata;

	if (spi->dev.of_node) {
		error = rmi_spi_of_probe(spi, pdata);
		if (error)
			return error;
	} else if (spi_pdata) {
		*pdata = *spi_pdata;
	}

	if (pdata->spi_data.bits_per_word)
		spi->bits_per_word = pdata->spi_data.bits_per_word;

	if (pdata->spi_data.mode)
		spi->mode = pdata->spi_data.mode;

	error = spi_setup(spi);
	if (error < 0) {
		dev_err(&spi->dev, "spi_setup failed!\n");
		return error;
	}

	pdata->irq = spi->irq;

	rmi_spi->spi = spi;
	mutex_init(&rmi_spi->page_mutex);

	rmi_spi->xport.dev = &spi->dev;
	rmi_spi->xport.proto_name = "spi";
	rmi_spi->xport.ops = &rmi_spi_ops;

	spi_set_drvdata(spi, rmi_spi);

	error = rmi_spi_manage_pools(rmi_spi, RMI_SPI_DEFAULT_XFER_BUF_SIZE);
	if (error)
		return error;

	/*
	 * Setting the page to zero will (a) make sure the PSR is in a
	 * known state, and (b) make sure we can talk to the device.
	 */
	error = rmi_set_page(rmi_spi, 0);
	if (error) {
		dev_err(&spi->dev, "Failed to set page select to 0.\n");
		return error;
	}

	dev_info(&spi->dev, "registering SPI-connected sensor\n");

	error = rmi_register_transport_device(&rmi_spi->xport);
	if (error) {
		dev_err(&spi->dev, "failed to register sensor: %d\n", error);
		return error;
	}

	error = devm_add_action_or_reset(&spi->dev,
					  rmi_spi_unregister_transport,
					  rmi_spi);
	if (error)
		return error;

	return 0;
}