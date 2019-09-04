#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct spi_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;
struct fpga_manager {int dummy; } ;
struct altera_ps_conf {int /*<<< orphan*/  mgr_name; void* confd; void* status; void* config; struct spi_device* spi; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  altera_ps_ops ; 
 char* dev_driver_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct altera_ps_conf* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct fpga_manager* fpga_mgr_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct altera_ps_conf*) ; 
 int /*<<< orphan*/  fpga_mgr_free (struct fpga_manager*) ; 
 int fpga_mgr_register (struct fpga_manager*) ; 
 int /*<<< orphan*/  of_ef_match ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct fpga_manager*) ; 

__attribute__((used)) static int altera_ps_probe(struct spi_device *spi)
{
	struct altera_ps_conf *conf;
	const struct of_device_id *of_id;
	struct fpga_manager *mgr;
	int ret;

	conf = devm_kzalloc(&spi->dev, sizeof(*conf), GFP_KERNEL);
	if (!conf)
		return -ENOMEM;

	of_id = of_match_device(of_ef_match, &spi->dev);
	if (!of_id)
		return -ENODEV;

	conf->data = of_id->data;
	conf->spi = spi;
	conf->config = devm_gpiod_get(&spi->dev, "nconfig", GPIOD_OUT_LOW);
	if (IS_ERR(conf->config)) {
		dev_err(&spi->dev, "Failed to get config gpio: %ld\n",
			PTR_ERR(conf->config));
		return PTR_ERR(conf->config);
	}

	conf->status = devm_gpiod_get(&spi->dev, "nstat", GPIOD_IN);
	if (IS_ERR(conf->status)) {
		dev_err(&spi->dev, "Failed to get status gpio: %ld\n",
			PTR_ERR(conf->status));
		return PTR_ERR(conf->status);
	}

	conf->confd = devm_gpiod_get(&spi->dev, "confd", GPIOD_IN);
	if (IS_ERR(conf->confd)) {
		dev_warn(&spi->dev, "Not using confd gpio: %ld\n",
			 PTR_ERR(conf->confd));
	}

	/* Register manager with unique name */
	snprintf(conf->mgr_name, sizeof(conf->mgr_name), "%s %s",
		 dev_driver_string(&spi->dev), dev_name(&spi->dev));

	mgr = fpga_mgr_create(&spi->dev, conf->mgr_name,
			      &altera_ps_ops, conf);
	if (!mgr)
		return -ENOMEM;

	spi_set_drvdata(spi, mgr);

	ret = fpga_mgr_register(mgr);
	if (ret)
		fpga_mgr_free(mgr);

	return ret;
}