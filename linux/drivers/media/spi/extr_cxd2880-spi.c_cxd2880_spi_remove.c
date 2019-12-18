#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* remove_frontend ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ dmx; } ;
struct cxd2880_dvb_spi {scalar_t__ vcc_supply; int /*<<< orphan*/  adapter; int /*<<< orphan*/  dvb_fe; TYPE_2__ demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  dmx_fe; } ;

/* Variables and functions */
 int EINVAL ; 
 struct cxd2880_dvb_spi* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_dmx_release (TYPE_2__*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_frontend_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cxd2880_dvb_spi*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cxd2880_spi_remove(struct spi_device *spi)
{
	struct cxd2880_dvb_spi *dvb_spi;

	if (!spi) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}

	dvb_spi = dev_get_drvdata(&spi->dev);

	if (!dvb_spi) {
		pr_err("failed\n");
		return -EINVAL;
	}
	dvb_spi->demux.dmx.remove_frontend(&dvb_spi->demux.dmx,
					   &dvb_spi->dmx_fe);
	dvb_dmxdev_release(&dvb_spi->dmxdev);
	dvb_dmx_release(&dvb_spi->demux);
	dvb_unregister_frontend(&dvb_spi->dvb_fe);
	dvb_frontend_detach(&dvb_spi->dvb_fe);
	dvb_unregister_adapter(&dvb_spi->adapter);

	if (dvb_spi->vcc_supply)
		regulator_disable(dvb_spi->vcc_supply);

	kfree(dvb_spi);
	pr_info("cxd2880_spi remove ok.\n");

	return 0;
}