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
struct spi_mpc8xxx_cs {int hw_mode; } ;
struct spi_device {int mode; int /*<<< orphan*/  master; int /*<<< orphan*/  max_speed_hz; } ;
struct mpc8xxx_spi {struct fsl_spi_reg* reg_base; } ;
struct fsl_spi_reg {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITBANG_CS_INACTIVE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LOOP ; 
 int SPI_LSB_FIRST ; 
 int SPMODE_CI_INACTIVEHIGH ; 
 int SPMODE_CP_BEGIN_EDGECLK ; 
 int SPMODE_LOOP ; 
 int SPMODE_REV ; 
 int /*<<< orphan*/  fsl_spi_chipselect (struct spi_device*,int /*<<< orphan*/ ) ; 
 int fsl_spi_setup_transfer (struct spi_device*,int /*<<< orphan*/ *) ; 
 struct spi_mpc8xxx_cs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mpc8xxx_spi_read_reg (int /*<<< orphan*/ *) ; 
 struct spi_mpc8xxx_cs* spi_get_ctldata (struct spi_device*) ; 
 struct mpc8xxx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_ctldata (struct spi_device*,struct spi_mpc8xxx_cs*) ; 

__attribute__((used)) static int fsl_spi_setup(struct spi_device *spi)
{
	struct mpc8xxx_spi *mpc8xxx_spi;
	struct fsl_spi_reg *reg_base;
	int retval;
	u32 hw_mode;
	struct spi_mpc8xxx_cs *cs = spi_get_ctldata(spi);

	if (!spi->max_speed_hz)
		return -EINVAL;

	if (!cs) {
		cs = kzalloc(sizeof(*cs), GFP_KERNEL);
		if (!cs)
			return -ENOMEM;
		spi_set_ctldata(spi, cs);
	}
	mpc8xxx_spi = spi_master_get_devdata(spi->master);

	reg_base = mpc8xxx_spi->reg_base;

	hw_mode = cs->hw_mode; /* Save original settings */
	cs->hw_mode = mpc8xxx_spi_read_reg(&reg_base->mode);
	/* mask out bits we are going to set */
	cs->hw_mode &= ~(SPMODE_CP_BEGIN_EDGECLK | SPMODE_CI_INACTIVEHIGH
			 | SPMODE_REV | SPMODE_LOOP);

	if (spi->mode & SPI_CPHA)
		cs->hw_mode |= SPMODE_CP_BEGIN_EDGECLK;
	if (spi->mode & SPI_CPOL)
		cs->hw_mode |= SPMODE_CI_INACTIVEHIGH;
	if (!(spi->mode & SPI_LSB_FIRST))
		cs->hw_mode |= SPMODE_REV;
	if (spi->mode & SPI_LOOP)
		cs->hw_mode |= SPMODE_LOOP;

	retval = fsl_spi_setup_transfer(spi, NULL);
	if (retval < 0) {
		cs->hw_mode = hw_mode; /* Restore settings */
		return retval;
	}

	/* Initialize chipselect - might be active for SPI_CS_HIGH mode */
	fsl_spi_chipselect(spi, BITBANG_CS_INACTIVE);

	return 0;
}