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
typedef  int u16 ;
struct omap_i2c_dev {scalar_t__ rev; int flags; int speed; int iestate; int pscstate; int scllstate; int sclhstate; int bb_valid; scalar_t__ fifo_size; int /*<<< orphan*/  dev; int /*<<< orphan*/  westate; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int OMAP_I2C_FLAG_ALWAYS_ARMXOR_CLK ; 
 int OMAP_I2C_FLAG_FORCE_19200_INT_CLK ; 
 int OMAP_I2C_FLAG_SIMPLE_CLOCK ; 
 int OMAP_I2C_IE_AL ; 
 int OMAP_I2C_IE_ARDY ; 
 int OMAP_I2C_IE_NACK ; 
 int OMAP_I2C_IE_RDR ; 
 int OMAP_I2C_IE_RRDY ; 
 int OMAP_I2C_IE_XDR ; 
 int OMAP_I2C_IE_XRDY ; 
 scalar_t__ OMAP_I2C_REV_ON_3430_3530 ; 
 int OMAP_I2C_SCLH_HSSCLH ; 
 int OMAP_I2C_SCLL_HSSCLL ; 
 int /*<<< orphan*/  OMAP_I2C_WE_ALL ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  __omap_i2c_init (struct omap_i2c_dev*) ; 
 struct clk* clk_get (int /*<<< orphan*/ ,char*) ; 
 int clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int omap_i2c_init(struct omap_i2c_dev *omap)
{
	u16 psc = 0, scll = 0, sclh = 0;
	u16 fsscll = 0, fssclh = 0, hsscll = 0, hssclh = 0;
	unsigned long fclk_rate = 12000000;
	unsigned long internal_clk = 0;
	struct clk *fclk;
	int error;

	if (omap->rev >= OMAP_I2C_REV_ON_3430_3530) {
		/*
		 * Enabling all wakup sources to stop I2C freezing on
		 * WFI instruction.
		 * REVISIT: Some wkup sources might not be needed.
		 */
		omap->westate = OMAP_I2C_WE_ALL;
	}

	if (omap->flags & OMAP_I2C_FLAG_ALWAYS_ARMXOR_CLK) {
		/*
		 * The I2C functional clock is the armxor_ck, so there's
		 * no need to get "armxor_ck" separately.  Now, if OMAP2420
		 * always returns 12MHz for the functional clock, we can
		 * do this bit unconditionally.
		 */
		fclk = clk_get(omap->dev, "fck");
		if (IS_ERR(fclk)) {
			error = PTR_ERR(fclk);
			dev_err(omap->dev, "could not get fck: %i\n", error);

			return error;
		}

		fclk_rate = clk_get_rate(fclk);
		clk_put(fclk);

		/* TRM for 5912 says the I2C clock must be prescaled to be
		 * between 7 - 12 MHz. The XOR input clock is typically
		 * 12, 13 or 19.2 MHz. So we should have code that produces:
		 *
		 * XOR MHz	Divider		Prescaler
		 * 12		1		0
		 * 13		2		1
		 * 19.2		2		1
		 */
		if (fclk_rate > 12000000)
			psc = fclk_rate / 12000000;
	}

	if (!(omap->flags & OMAP_I2C_FLAG_SIMPLE_CLOCK)) {

		/*
		 * HSI2C controller internal clk rate should be 19.2 Mhz for
		 * HS and for all modes on 2430. On 34xx we can use lower rate
		 * to get longer filter period for better noise suppression.
		 * The filter is iclk (fclk for HS) period.
		 */
		if (omap->speed > 400 ||
			       omap->flags & OMAP_I2C_FLAG_FORCE_19200_INT_CLK)
			internal_clk = 19200;
		else if (omap->speed > 100)
			internal_clk = 9600;
		else
			internal_clk = 4000;
		fclk = clk_get(omap->dev, "fck");
		if (IS_ERR(fclk)) {
			error = PTR_ERR(fclk);
			dev_err(omap->dev, "could not get fck: %i\n", error);

			return error;
		}
		fclk_rate = clk_get_rate(fclk) / 1000;
		clk_put(fclk);

		/* Compute prescaler divisor */
		psc = fclk_rate / internal_clk;
		psc = psc - 1;

		/* If configured for High Speed */
		if (omap->speed > 400) {
			unsigned long scl;

			/* For first phase of HS mode */
			scl = internal_clk / 400;
			fsscll = scl - (scl / 3) - 7;
			fssclh = (scl / 3) - 5;

			/* For second phase of HS mode */
			scl = fclk_rate / omap->speed;
			hsscll = scl - (scl / 3) - 7;
			hssclh = (scl / 3) - 5;
		} else if (omap->speed > 100) {
			unsigned long scl;

			/* Fast mode */
			scl = internal_clk / omap->speed;
			fsscll = scl - (scl / 3) - 7;
			fssclh = (scl / 3) - 5;
		} else {
			/* Standard mode */
			fsscll = internal_clk / (omap->speed * 2) - 7;
			fssclh = internal_clk / (omap->speed * 2) - 5;
		}
		scll = (hsscll << OMAP_I2C_SCLL_HSSCLL) | fsscll;
		sclh = (hssclh << OMAP_I2C_SCLH_HSSCLH) | fssclh;
	} else {
		/* Program desired operating rate */
		fclk_rate /= (psc + 1) * 1000;
		if (psc > 2)
			psc = 2;
		scll = fclk_rate / (omap->speed * 2) - 7 + psc;
		sclh = fclk_rate / (omap->speed * 2) - 7 + psc;
	}

	omap->iestate = (OMAP_I2C_IE_XRDY | OMAP_I2C_IE_RRDY |
			OMAP_I2C_IE_ARDY | OMAP_I2C_IE_NACK |
			OMAP_I2C_IE_AL)  | ((omap->fifo_size) ?
				(OMAP_I2C_IE_RDR | OMAP_I2C_IE_XDR) : 0);

	omap->pscstate = psc;
	omap->scllstate = scll;
	omap->sclhstate = sclh;

	if (omap->rev <= OMAP_I2C_REV_ON_3430_3530) {
		/* Not implemented */
		omap->bb_valid = 1;
	}

	__omap_i2c_init(omap);

	return 0;
}