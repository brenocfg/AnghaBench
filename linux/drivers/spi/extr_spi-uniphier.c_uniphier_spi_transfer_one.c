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
struct uniphier_spi_priv {int speed_hz; } ;
struct spi_transfer {unsigned long len; } ;
struct spi_master {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 unsigned long DIV_ROUND_UP (int,int) ; 
 int SSI_POLL_TIMEOUT_US ; 
 int USEC_PER_SEC ; 
 struct uniphier_spi_priv* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  uniphier_spi_setup_transfer (struct spi_device*,struct spi_transfer*) ; 
 int uniphier_spi_transfer_one_irq (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 
 int uniphier_spi_transfer_one_poll (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 

__attribute__((used)) static int uniphier_spi_transfer_one(struct spi_master *master,
				     struct spi_device *spi,
				     struct spi_transfer *t)
{
	struct uniphier_spi_priv *priv = spi_master_get_devdata(master);
	unsigned long threshold;

	/* Terminate and return success for 0 byte length transfer */
	if (!t->len)
		return 0;

	uniphier_spi_setup_transfer(spi, t);

	/*
	 * If the transfer operation will take longer than
	 * SSI_POLL_TIMEOUT_US, it should use irq.
	 */
	threshold = DIV_ROUND_UP(SSI_POLL_TIMEOUT_US * priv->speed_hz,
					USEC_PER_SEC * BITS_PER_BYTE);
	if (t->len > threshold)
		return uniphier_spi_transfer_one_irq(master, spi, t);
	else
		return uniphier_spi_transfer_one_poll(master, spi, t);
}