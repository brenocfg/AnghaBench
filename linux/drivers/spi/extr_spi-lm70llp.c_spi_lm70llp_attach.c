#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct spi_master {int dummy; } ;
struct TYPE_9__ {size_t flags; struct spi_master* master; int /*<<< orphan*/ * txrx_word; int /*<<< orphan*/  chipselect; } ;
struct TYPE_8__ {int max_speed_hz; size_t mode; struct spi_lm70llp* controller_data; scalar_t__ chip_select; int /*<<< orphan*/  modalias; } ;
struct spi_lm70llp {struct pardevice* pd; struct parport* port; TYPE_4__ bitbang; TYPE_2__* spidev_lm70; TYPE_3__ info; } ;
struct parport {TYPE_1__* physport; } ;
struct pardevice {int /*<<< orphan*/  dev; } ;
struct pardev_cb {int /*<<< orphan*/  flags; struct spi_lm70llp* private; } ;
typedef  int /*<<< orphan*/  lm70llp_cb ;
struct TYPE_7__ {int bits_per_word; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRVNAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PARPORT_FLAG_EXCL ; 
 size_t SPI_3WIRE ; 
 size_t SPI_MODE_0 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lm70_INIT ; 
 int /*<<< orphan*/  lm70_chipselect ; 
 int /*<<< orphan*/  lm70_txrx ; 
 struct spi_lm70llp* lm70llp ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memset (struct pardev_cb*,int /*<<< orphan*/ ,int) ; 
 int parport_claim (struct pardevice*) ; 
 struct pardevice* parport_register_dev_model (struct parport*,int /*<<< orphan*/ ,struct pardev_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_release (struct pardevice*) ; 
 int /*<<< orphan*/  parport_unregister_device (struct pardevice*) ; 
 int /*<<< orphan*/  parport_write_data (struct parport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 struct spi_master* spi_alloc_master (int /*<<< orphan*/ ,int) ; 
 int spi_bitbang_start (TYPE_4__*) ; 
 int /*<<< orphan*/  spi_bitbang_stop (TYPE_4__*) ; 
 struct spi_lm70llp* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 TYPE_2__* spi_new_device (struct spi_master*,TYPE_3__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void spi_lm70llp_attach(struct parport *p)
{
	struct pardevice	*pd;
	struct spi_lm70llp	*pp;
	struct spi_master	*master;
	int			status;
	struct pardev_cb	lm70llp_cb;

	if (lm70llp) {
		pr_warn("spi_lm70llp instance already loaded. Aborting.\n");
		return;
	}

	/* TODO:  this just _assumes_ a lm70 is there ... no probe;
	 * the lm70 driver could verify it, reading the manf ID.
	 */

	master = spi_alloc_master(p->physport->dev, sizeof *pp);
	if (!master) {
		status = -ENOMEM;
		goto out_fail;
	}
	pp = spi_master_get_devdata(master);

	/*
	 * SPI and bitbang hookup.
	 */
	pp->bitbang.master = master;
	pp->bitbang.chipselect = lm70_chipselect;
	pp->bitbang.txrx_word[SPI_MODE_0] = lm70_txrx;
	pp->bitbang.flags = SPI_3WIRE;

	/*
	 * Parport hookup
	 */
	pp->port = p;
	memset(&lm70llp_cb, 0, sizeof(lm70llp_cb));
	lm70llp_cb.private = pp;
	lm70llp_cb.flags = PARPORT_FLAG_EXCL;
	pd = parport_register_dev_model(p, DRVNAME, &lm70llp_cb, 0);

	if (!pd) {
		status = -ENOMEM;
		goto out_free_master;
	}
	pp->pd = pd;

	status = parport_claim(pd);
	if (status < 0)
		goto out_parport_unreg;

	/*
	 * Start SPI ...
	 */
	status = spi_bitbang_start(&pp->bitbang);
	if (status < 0) {
		dev_warn(&pd->dev, "spi_bitbang_start failed with status %d\n",
			 status);
		goto out_off_and_release;
	}

	/*
	 * The modalias name MUST match the device_driver name
	 * for the bus glue code to match and subsequently bind them.
	 * We are binding to the generic drivers/hwmon/lm70.c device
	 * driver.
	 */
	strcpy(pp->info.modalias, "lm70");
	pp->info.max_speed_hz = 6 * 1000 * 1000;
	pp->info.chip_select = 0;
	pp->info.mode = SPI_3WIRE | SPI_MODE_0;

	/* power up the chip, and let the LM70 control SI/SO */
	parport_write_data(pp->port, lm70_INIT);

	/* Enable access to our primary data structure via
	 * the board info's (void *)controller_data.
	 */
	pp->info.controller_data = pp;
	pp->spidev_lm70 = spi_new_device(pp->bitbang.master, &pp->info);
	if (pp->spidev_lm70)
		dev_dbg(&pp->spidev_lm70->dev, "spidev_lm70 at %s\n",
			dev_name(&pp->spidev_lm70->dev));
	else {
		dev_warn(&pd->dev, "spi_new_device failed\n");
		status = -ENODEV;
		goto out_bitbang_stop;
	}
	pp->spidev_lm70->bits_per_word = 8;

	lm70llp = pp;
	return;

out_bitbang_stop:
	spi_bitbang_stop(&pp->bitbang);
out_off_and_release:
	/* power down */
	parport_write_data(pp->port, 0);
	mdelay(10);
	parport_release(pp->pd);
out_parport_unreg:
	parport_unregister_device(pd);
out_free_master:
	spi_master_put(master);
out_fail:
	pr_info("spi_lm70llp probe fail, status %d\n", status);
}