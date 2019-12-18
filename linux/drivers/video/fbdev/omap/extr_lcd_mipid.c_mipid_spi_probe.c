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
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct mipid_device {int /*<<< orphan*/  panel; struct spi_device* spi; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct mipid_device*) ; 
 struct mipid_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mipid_detect (struct mipid_device*) ; 
 int /*<<< orphan*/  mipid_panel ; 
 int /*<<< orphan*/  omapfb_register_panel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mipid_spi_probe(struct spi_device *spi)
{
	struct mipid_device *md;
	int r;

	md = kzalloc(sizeof(*md), GFP_KERNEL);
	if (md == NULL) {
		dev_err(&spi->dev, "out of memory\n");
		return -ENOMEM;
	}

	spi->mode = SPI_MODE_0;
	md->spi = spi;
	dev_set_drvdata(&spi->dev, md);
	md->panel = mipid_panel;

	r = mipid_detect(md);
	if (r < 0)
		return r;

	omapfb_register_panel(&md->panel);

	return 0;
}