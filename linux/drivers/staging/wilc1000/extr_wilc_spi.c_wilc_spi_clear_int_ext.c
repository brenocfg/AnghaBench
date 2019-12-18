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
typedef  int u32 ;
struct wilc_spi {int nint; scalar_t__ has_thrpt_enh; } ;
struct wilc {struct wilc_spi* bus_data; int /*<<< orphan*/  dev; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EN_VMM ; 
 int MAX_NUM_INT ; 
 int SEL_VMM_TBL0 ; 
 int SEL_VMM_TBL1 ; 
 scalar_t__ WILC_SPI_REG_BASE ; 
 int WILC_VMM_CORE_CTL ; 
 int WILC_VMM_TBL_CTL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int spi_internal_write (struct wilc*,scalar_t__,int) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 
 int wilc_spi_write_reg (struct wilc*,int,int) ; 

__attribute__((used)) static int wilc_spi_clear_int_ext(struct wilc *wilc, u32 val)
{
	struct spi_device *spi = to_spi_device(wilc->dev);
	struct wilc_spi *spi_priv = wilc->bus_data;
	int ret;
	u32 flags;
	u32 tbl_ctl;

	if (spi_priv->has_thrpt_enh) {
		return spi_internal_write(wilc, 0xe844 - WILC_SPI_REG_BASE,
					  val);
	}

	flags = val & (BIT(MAX_NUM_INT) - 1);
	if (flags) {
		int i;

		ret = 1;
		for (i = 0; i < spi_priv->nint; i++) {
			/*
			 * No matter what you write 1 or 0,
			 * it will clear interrupt.
			 */
			if (flags & 1)
				ret = wilc_spi_write_reg(wilc,
							 0x10c8 + i * 4, 1);
			if (!ret)
				break;
			flags >>= 1;
		}
		if (!ret) {
			dev_err(&spi->dev,
				"Failed wilc_spi_write_reg, set reg %x ...\n",
				0x10c8 + i * 4);
			return ret;
		}
		for (i = spi_priv->nint; i < MAX_NUM_INT; i++) {
			if (flags & 1)
				dev_err(&spi->dev,
					"Unexpected interrupt cleared %d...\n",
					i);
			flags >>= 1;
		}
	}

	tbl_ctl = 0;
	/* select VMM table 0 */
	if (val & SEL_VMM_TBL0)
		tbl_ctl |= BIT(0);
	/* select VMM table 1 */
	if (val & SEL_VMM_TBL1)
		tbl_ctl |= BIT(1);

	ret = wilc_spi_write_reg(wilc, WILC_VMM_TBL_CTL, tbl_ctl);
	if (!ret) {
		dev_err(&spi->dev, "fail write reg vmm_tbl_ctl...\n");
		return ret;
	}

	if (val & EN_VMM) {
		/*
		 * enable vmm transfer.
		 */
		ret = wilc_spi_write_reg(wilc, WILC_VMM_CORE_CTL, 1);
		if (!ret) {
			dev_err(&spi->dev, "fail write reg vmm_core_ctl...\n");
			return ret;
		}
	}

	return ret;
}