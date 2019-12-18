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
typedef  int u32 ;
struct sh_msiof_spi_priv {unsigned int min_div_pow; TYPE_2__* ctlr; TYPE_1__* pdev; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 
 int /*<<< orphan*/  RSCR ; 
 int SCR_BRPS (int) ; 
 int SPI_CONTROLLER_MUST_TX ; 
 int /*<<< orphan*/  TSCR ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned long,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int* sh_msiof_spi_div_array ; 
 int /*<<< orphan*/  sh_msiof_write (struct sh_msiof_spi_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sh_msiof_spi_set_clk_regs(struct sh_msiof_spi_priv *p,
				      unsigned long parent_rate, u32 spi_hz)
{
	unsigned long div;
	u32 brps, scr;
	unsigned int div_pow = p->min_div_pow;

	if (!spi_hz || !parent_rate) {
		WARN(1, "Invalid clock rate parameters %lu and %u\n",
		     parent_rate, spi_hz);
		return;
	}

	div = DIV_ROUND_UP(parent_rate, spi_hz);
	if (div <= 1024) {
		/* SCR_BRDV_DIV_1 is valid only if BRPS is x 1/1 or x 1/2 */
		if (!div_pow && div <= 32 && div > 2)
			div_pow = 1;

		if (div_pow)
			brps = (div + 1) >> div_pow;
		else
			brps = div;

		for (; brps > 32; div_pow++)
			brps = (brps + 1) >> 1;
	} else {
		/* Set transfer rate composite divisor to 2^5 * 32 = 1024 */
		dev_err(&p->pdev->dev,
			"Requested SPI transfer rate %d is too low\n", spi_hz);
		div_pow = 5;
		brps = 32;
	}

	scr = sh_msiof_spi_div_array[div_pow] | SCR_BRPS(brps);
	sh_msiof_write(p, TSCR, scr);
	if (!(p->ctlr->flags & SPI_CONTROLLER_MUST_TX))
		sh_msiof_write(p, RSCR, scr);
}