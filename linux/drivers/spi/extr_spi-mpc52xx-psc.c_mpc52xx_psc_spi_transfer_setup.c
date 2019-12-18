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
struct spi_transfer {int bits_per_word; scalar_t__ speed_hz; } ;
struct spi_device {int bits_per_word; scalar_t__ max_speed_hz; struct mpc52xx_psc_spi_cs* controller_state; } ;
struct mpc52xx_psc_spi_cs {int bits_per_word; scalar_t__ speed_hz; } ;

/* Variables and functions */

__attribute__((used)) static int mpc52xx_psc_spi_transfer_setup(struct spi_device *spi,
		struct spi_transfer *t)
{
	struct mpc52xx_psc_spi_cs *cs = spi->controller_state;

	cs->speed_hz = (t && t->speed_hz)
			? t->speed_hz : spi->max_speed_hz;
	cs->bits_per_word = (t && t->bits_per_word)
			? t->bits_per_word : spi->bits_per_word;
	cs->bits_per_word = ((cs->bits_per_word + 7) / 8) * 8;
	return 0;
}