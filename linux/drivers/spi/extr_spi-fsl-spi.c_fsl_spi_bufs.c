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
typedef  int u8 ;
struct spi_transfer {unsigned int len; int bits_per_word; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  master; } ;
struct mpc8xxx_spi {int flags; int count; int /*<<< orphan*/  done; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; struct fsl_spi_reg* reg_base; } ;
struct fsl_spi_reg {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int SPI_CPM_MODE ; 
 int fsl_spi_cpm_bufs (struct mpc8xxx_spi*,struct spi_transfer*,int) ; 
 int /*<<< orphan*/  fsl_spi_cpm_bufs_complete (struct mpc8xxx_spi*) ; 
 int fsl_spi_cpu_bufs (struct mpc8xxx_spi*,struct spi_transfer*,unsigned int) ; 
 int /*<<< orphan*/  mpc8xxx_spi_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct mpc8xxx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_spi_bufs(struct spi_device *spi, struct spi_transfer *t,
			    bool is_dma_mapped)
{
	struct mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(spi->master);
	struct fsl_spi_reg *reg_base;
	unsigned int len = t->len;
	u8 bits_per_word;
	int ret;

	reg_base = mpc8xxx_spi->reg_base;
	bits_per_word = spi->bits_per_word;
	if (t->bits_per_word)
		bits_per_word = t->bits_per_word;

	if (bits_per_word > 8) {
		/* invalid length? */
		if (len & 1)
			return -EINVAL;
		len /= 2;
	}
	if (bits_per_word > 16) {
		/* invalid length? */
		if (len & 1)
			return -EINVAL;
		len /= 2;
	}

	mpc8xxx_spi->tx = t->tx_buf;
	mpc8xxx_spi->rx = t->rx_buf;

	reinit_completion(&mpc8xxx_spi->done);

	if (mpc8xxx_spi->flags & SPI_CPM_MODE)
		ret = fsl_spi_cpm_bufs(mpc8xxx_spi, t, is_dma_mapped);
	else
		ret = fsl_spi_cpu_bufs(mpc8xxx_spi, t, len);
	if (ret)
		return ret;

	wait_for_completion(&mpc8xxx_spi->done);

	/* disable rx ints */
	mpc8xxx_spi_write_reg(&reg_base->mask, 0);

	if (mpc8xxx_spi->flags & SPI_CPM_MODE)
		fsl_spi_cpm_bufs_complete(mpc8xxx_spi);

	return mpc8xxx_spi->count;
}