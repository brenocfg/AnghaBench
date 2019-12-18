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
typedef  int u32 ;
struct spi_device {int mode; scalar_t__ cs_gpiod; int /*<<< orphan*/  controller; } ;
struct sh_msiof_spi_priv {int native_cs_inited; int native_cs_high; TYPE_1__* pdev; int /*<<< orphan*/  ctlr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDR1_SYNCAC_SHIFT ; 
 int MDR1_SYNCMD_MASK ; 
 int MDR1_SYNCMD_SPI ; 
 int MDR1_TRMD ; 
 int /*<<< orphan*/  RMDR1 ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  TMDR1 ; 
 int TMDR1_PCON ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int sh_msiof_read (struct sh_msiof_spi_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_msiof_write (struct sh_msiof_spi_priv*,int /*<<< orphan*/ ,int) ; 
 struct sh_msiof_spi_priv* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 
 scalar_t__ spi_controller_is_slave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_msiof_spi_setup(struct spi_device *spi)
{
	struct sh_msiof_spi_priv *p =
		spi_controller_get_devdata(spi->controller);
	u32 clr, set, tmp;

	if (spi->cs_gpiod || spi_controller_is_slave(p->ctlr))
		return 0;

	if (p->native_cs_inited &&
	    (p->native_cs_high == !!(spi->mode & SPI_CS_HIGH)))
		return 0;

	/* Configure native chip select mode/polarity early */
	clr = MDR1_SYNCMD_MASK;
	set = MDR1_SYNCMD_SPI;
	if (spi->mode & SPI_CS_HIGH)
		clr |= BIT(MDR1_SYNCAC_SHIFT);
	else
		set |= BIT(MDR1_SYNCAC_SHIFT);
	pm_runtime_get_sync(&p->pdev->dev);
	tmp = sh_msiof_read(p, TMDR1) & ~clr;
	sh_msiof_write(p, TMDR1, tmp | set | MDR1_TRMD | TMDR1_PCON);
	tmp = sh_msiof_read(p, RMDR1) & ~clr;
	sh_msiof_write(p, RMDR1, tmp | set);
	pm_runtime_put(&p->pdev->dev);
	p->native_cs_high = spi->mode & SPI_CS_HIGH;
	p->native_cs_inited = true;
	return 0;
}