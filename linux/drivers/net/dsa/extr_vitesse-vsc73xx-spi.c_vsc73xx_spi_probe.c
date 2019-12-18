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
struct TYPE_2__ {int /*<<< orphan*/ * ops; struct vsc73xx_spi* priv; struct device* dev; } ;
struct vsc73xx_spi {TYPE_1__ vsc; int /*<<< orphan*/  lock; int /*<<< orphan*/  spi; } ;
struct device {int dummy; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  mode; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct vsc73xx_spi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_dev_get (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct vsc73xx_spi*) ; 
 int spi_setup (struct spi_device*) ; 
 int vsc73xx_probe (TYPE_1__*) ; 
 int /*<<< orphan*/  vsc73xx_spi_ops ; 

__attribute__((used)) static int vsc73xx_spi_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct vsc73xx_spi *vsc_spi;
	int ret;

	vsc_spi = devm_kzalloc(dev, sizeof(*vsc_spi), GFP_KERNEL);
	if (!vsc_spi)
		return -ENOMEM;

	spi_set_drvdata(spi, vsc_spi);
	vsc_spi->spi = spi_dev_get(spi);
	vsc_spi->vsc.dev = dev;
	vsc_spi->vsc.priv = vsc_spi;
	vsc_spi->vsc.ops = &vsc73xx_spi_ops;
	mutex_init(&vsc_spi->lock);

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(dev, "spi setup failed.\n");
		return ret;
	}

	return vsc73xx_probe(&vsc_spi->vsc);
}