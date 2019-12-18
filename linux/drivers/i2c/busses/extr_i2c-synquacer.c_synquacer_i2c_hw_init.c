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
typedef  int /*<<< orphan*/  u32 ;
struct synquacer_i2c {int speed_khz; scalar_t__ base; int /*<<< orphan*/  pclkrate; } ;

/* Variables and functions */
 unsigned char SYNQUACER_I2C_BUS_CLK_FR (int /*<<< orphan*/ ) ; 
 unsigned char SYNQUACER_I2C_CCR_CS_FAST_MAX_18M (int /*<<< orphan*/ ) ; 
 unsigned char SYNQUACER_I2C_CCR_CS_FAST_MIN_18M (int /*<<< orphan*/ ) ; 
 unsigned char SYNQUACER_I2C_CCR_CS_STD_MAX_18M (int /*<<< orphan*/ ) ; 
 unsigned char SYNQUACER_I2C_CCR_CS_STD_MIN_18M (int /*<<< orphan*/ ) ; 
 unsigned char SYNQUACER_I2C_CCR_EN ; 
 unsigned char SYNQUACER_I2C_CCR_FM ; 
 int /*<<< orphan*/  SYNQUACER_I2C_CLK_RATE_18M ; 
 unsigned char SYNQUACER_I2C_CSR_CS_FAST_MAX_18M (int /*<<< orphan*/ ) ; 
 unsigned char SYNQUACER_I2C_CSR_CS_FAST_MIN_18M (int /*<<< orphan*/ ) ; 
 unsigned char SYNQUACER_I2C_CSR_CS_STD_MAX_18M (int /*<<< orphan*/ ) ; 
 unsigned char SYNQUACER_I2C_CSR_CS_STD_MIN_18M (int /*<<< orphan*/ ) ; 
 scalar_t__ SYNQUACER_I2C_REG_ADR ; 
 scalar_t__ SYNQUACER_I2C_REG_BC2R ; 
 scalar_t__ SYNQUACER_I2C_REG_BCR ; 
 scalar_t__ SYNQUACER_I2C_REG_CCR ; 
 scalar_t__ SYNQUACER_I2C_REG_CSR ; 
 scalar_t__ SYNQUACER_I2C_REG_FSR ; 
#define  SYNQUACER_I2C_SPEED_FM 129 
#define  SYNQUACER_I2C_SPEED_SM 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  writeb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void synquacer_i2c_hw_init(struct synquacer_i2c *i2c)
{
	unsigned char ccr_cs, csr_cs;
	u32 rt = i2c->pclkrate;

	/* Set own Address */
	writeb(0, i2c->base + SYNQUACER_I2C_REG_ADR);

	/* Set PCLK frequency */
	writeb(SYNQUACER_I2C_BUS_CLK_FR(i2c->pclkrate),
	       i2c->base + SYNQUACER_I2C_REG_FSR);

	switch (i2c->speed_khz) {
	case SYNQUACER_I2C_SPEED_FM:
		if (i2c->pclkrate <= SYNQUACER_I2C_CLK_RATE_18M) {
			ccr_cs = SYNQUACER_I2C_CCR_CS_FAST_MAX_18M(rt);
			csr_cs = SYNQUACER_I2C_CSR_CS_FAST_MAX_18M(rt);
		} else {
			ccr_cs = SYNQUACER_I2C_CCR_CS_FAST_MIN_18M(rt);
			csr_cs = SYNQUACER_I2C_CSR_CS_FAST_MIN_18M(rt);
		}

		/* Set Clock and enable, Set fast mode */
		writeb(ccr_cs | SYNQUACER_I2C_CCR_FM |
		       SYNQUACER_I2C_CCR_EN,
		       i2c->base + SYNQUACER_I2C_REG_CCR);
		writeb(csr_cs, i2c->base + SYNQUACER_I2C_REG_CSR);
		break;
	case SYNQUACER_I2C_SPEED_SM:
		if (i2c->pclkrate <= SYNQUACER_I2C_CLK_RATE_18M) {
			ccr_cs = SYNQUACER_I2C_CCR_CS_STD_MAX_18M(rt);
			csr_cs = SYNQUACER_I2C_CSR_CS_STD_MAX_18M(rt);
		} else {
			ccr_cs = SYNQUACER_I2C_CCR_CS_STD_MIN_18M(rt);
			csr_cs = SYNQUACER_I2C_CSR_CS_STD_MIN_18M(rt);
		}

		/* Set Clock and enable, Set standard mode */
		writeb(ccr_cs | SYNQUACER_I2C_CCR_EN,
		      i2c->base + SYNQUACER_I2C_REG_CCR);
		writeb(csr_cs, i2c->base + SYNQUACER_I2C_REG_CSR);
		break;
	default:
		WARN_ON(1);
	}

	/* clear IRQ (INT=0, BER=0), Interrupt Disable */
	writeb(0, i2c->base + SYNQUACER_I2C_REG_BCR);
	writeb(0, i2c->base + SYNQUACER_I2C_REG_BC2R);
}