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
struct spi_device {int bits_per_word; int mode; int /*<<< orphan*/  dev; } ;
struct of_device_id {int dummy; } ;
struct cpcap_ddata {struct spi_device* spi; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * regmap_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SPI_CS_HIGH ; 
 int SPI_MODE_0 ; 
 int cpcap_check_revision (struct cpcap_ddata*) ; 
 int cpcap_init_irq (struct cpcap_ddata*) ; 
 int /*<<< orphan*/  cpcap_mfd_devices ; 
 int /*<<< orphan*/  cpcap_of_match ; 
 int /*<<< orphan*/  cpcap_regmap_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct cpcap_ddata* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct cpcap_ddata*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int cpcap_probe(struct spi_device *spi)
{
	const struct of_device_id *match;
	struct cpcap_ddata *cpcap;
	int ret;

	match = of_match_device(of_match_ptr(cpcap_of_match), &spi->dev);
	if (!match)
		return -ENODEV;

	cpcap = devm_kzalloc(&spi->dev, sizeof(*cpcap), GFP_KERNEL);
	if (!cpcap)
		return -ENOMEM;

	cpcap->spi = spi;
	spi_set_drvdata(spi, cpcap);

	spi->bits_per_word = 16;
	spi->mode = SPI_MODE_0 | SPI_CS_HIGH;

	ret = spi_setup(spi);
	if (ret)
		return ret;

	cpcap->regmap_conf = &cpcap_regmap_config;
	cpcap->regmap = devm_regmap_init_spi(spi, &cpcap_regmap_config);
	if (IS_ERR(cpcap->regmap)) {
		ret = PTR_ERR(cpcap->regmap);
		dev_err(&cpcap->spi->dev, "Failed to initialize regmap: %d\n",
			ret);

		return ret;
	}

	ret = cpcap_check_revision(cpcap);
	if (ret) {
		dev_err(&cpcap->spi->dev, "Failed to detect CPCAP: %i\n", ret);
		return ret;
	}

	ret = cpcap_init_irq(cpcap);
	if (ret)
		return ret;

	return devm_mfd_add_devices(&spi->dev, 0, cpcap_mfd_devices,
				    ARRAY_SIZE(cpcap_mfd_devices), NULL, 0, NULL);
}