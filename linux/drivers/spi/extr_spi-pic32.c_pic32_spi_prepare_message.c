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
typedef  int /*<<< orphan*/  u32 ;
struct spi_message {struct spi_device* spi; } ;
struct spi_master {int dummy; } ;
struct spi_device {scalar_t__ bits_per_word; scalar_t__ max_speed_hz; int mode; } ;
struct pic32_spi {scalar_t__ bits_per_word; scalar_t__ speed_hz; int mode; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_CKE ; 
 int /*<<< orphan*/  CTRL_CKP ; 
 int /*<<< orphan*/  CTRL_SMP ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int /*<<< orphan*/  pic32_spi_set_clk_rate (struct pic32_spi*,scalar_t__) ; 
 int /*<<< orphan*/  pic32_spi_set_word_size (struct pic32_spi*,scalar_t__) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 struct pic32_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pic32_spi_prepare_message(struct spi_master *master,
				     struct spi_message *msg)
{
	struct pic32_spi *pic32s = spi_master_get_devdata(master);
	struct spi_device *spi = msg->spi;
	u32 val;

	/* set device specific bits_per_word */
	if (pic32s->bits_per_word != spi->bits_per_word) {
		pic32_spi_set_word_size(pic32s, spi->bits_per_word);
		pic32s->bits_per_word = spi->bits_per_word;
	}

	/* device specific speed change */
	if (pic32s->speed_hz != spi->max_speed_hz) {
		pic32_spi_set_clk_rate(pic32s, spi->max_speed_hz);
		pic32s->speed_hz = spi->max_speed_hz;
	}

	/* device specific mode change */
	if (pic32s->mode != spi->mode) {
		val = readl(&pic32s->regs->ctrl);
		/* active low */
		if (spi->mode & SPI_CPOL)
			val |= CTRL_CKP;
		else
			val &= ~CTRL_CKP;
		/* tx on rising edge */
		if (spi->mode & SPI_CPHA)
			val &= ~CTRL_CKE;
		else
			val |= CTRL_CKE;

		/* rx at end of tx */
		val |= CTRL_SMP;
		writel(val, &pic32s->regs->ctrl);
		pic32s->mode = spi->mode;
	}

	return 0;
}