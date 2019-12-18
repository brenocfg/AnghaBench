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
struct ad_sigma_delta {int bus_locked; int keep_cs_asserted; int irq_dis; TYPE_1__* spi; int /*<<< orphan*/  completion; } ;
struct TYPE_2__ {int /*<<< orphan*/  master; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 unsigned int AD_SD_MODE_IDLE ; 
 int EIO ; 
 int HZ ; 
 int ad_sigma_delta_set_channel (struct ad_sigma_delta*,unsigned int) ; 
 int ad_sigma_delta_set_mode (struct ad_sigma_delta*,unsigned int) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bus_unlock (int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad_sd_calibrate(struct ad_sigma_delta *sigma_delta,
	unsigned int mode, unsigned int channel)
{
	int ret;
	unsigned long timeout;

	ret = ad_sigma_delta_set_channel(sigma_delta, channel);
	if (ret)
		return ret;

	spi_bus_lock(sigma_delta->spi->master);
	sigma_delta->bus_locked = true;
	sigma_delta->keep_cs_asserted = true;
	reinit_completion(&sigma_delta->completion);

	ret = ad_sigma_delta_set_mode(sigma_delta, mode);
	if (ret < 0)
		goto out;

	sigma_delta->irq_dis = false;
	enable_irq(sigma_delta->spi->irq);
	timeout = wait_for_completion_timeout(&sigma_delta->completion, 2 * HZ);
	if (timeout == 0) {
		sigma_delta->irq_dis = true;
		disable_irq_nosync(sigma_delta->spi->irq);
		ret = -EIO;
	} else {
		ret = 0;
	}
out:
	sigma_delta->keep_cs_asserted = false;
	ad_sigma_delta_set_mode(sigma_delta, AD_SD_MODE_IDLE);
	sigma_delta->bus_locked = false;
	spi_bus_unlock(sigma_delta->spi->master);

	return ret;
}