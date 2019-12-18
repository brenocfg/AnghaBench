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
struct sh_msiof_spi_priv {TYPE_1__* ctlr; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR ; 
 int CTR_REDG_SHIFT ; 
 int CTR_RSCKIZ_POL_SHIFT ; 
 int CTR_RSCKIZ_SCK ; 
 int CTR_TEDG_SHIFT ; 
 int CTR_TSCKIZ_POL_SHIFT ; 
 int CTR_TSCKIZ_SCK ; 
 int CTR_TXDIZ_HIZ ; 
 int CTR_TXDIZ_LOW ; 
 int MAX_SS ; 
 int MDR1_BITLSB_SHIFT ; 
 int MDR1_FLD_SHIFT ; 
 int MDR1_SYNCAC_SHIFT ; 
 int MDR1_SYNCMD_SPI ; 
 int MDR1_TRMD ; 
 int MDR1_XXSTP ; 
 int /*<<< orphan*/  RMDR1 ; 
 int SPI_CONTROLLER_MUST_TX ; 
 int /*<<< orphan*/  TMDR1 ; 
 int TMDR1_PCON ; 
 int TMDR1_SYNCCH_SHIFT ; 
 int sh_msiof_spi_get_dtdl_and_syncdl (struct sh_msiof_spi_priv*) ; 
 int /*<<< orphan*/  sh_msiof_write (struct sh_msiof_spi_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ spi_controller_is_slave (TYPE_1__*) ; 

__attribute__((used)) static void sh_msiof_spi_set_pin_regs(struct sh_msiof_spi_priv *p, u32 ss,
				      u32 cpol, u32 cpha,
				      u32 tx_hi_z, u32 lsb_first, u32 cs_high)
{
	u32 tmp;
	int edge;

	/*
	 * CPOL CPHA     TSCKIZ RSCKIZ TEDG REDG
	 *    0    0         10     10    1    1
	 *    0    1         10     10    0    0
	 *    1    0         11     11    0    0
	 *    1    1         11     11    1    1
	 */
	tmp = MDR1_SYNCMD_SPI | 1 << MDR1_FLD_SHIFT | MDR1_XXSTP;
	tmp |= !cs_high << MDR1_SYNCAC_SHIFT;
	tmp |= lsb_first << MDR1_BITLSB_SHIFT;
	tmp |= sh_msiof_spi_get_dtdl_and_syncdl(p);
	if (spi_controller_is_slave(p->ctlr)) {
		sh_msiof_write(p, TMDR1, tmp | TMDR1_PCON);
	} else {
		sh_msiof_write(p, TMDR1,
			       tmp | MDR1_TRMD | TMDR1_PCON |
			       (ss < MAX_SS ? ss : 0) << TMDR1_SYNCCH_SHIFT);
	}
	if (p->ctlr->flags & SPI_CONTROLLER_MUST_TX) {
		/* These bits are reserved if RX needs TX */
		tmp &= ~0x0000ffff;
	}
	sh_msiof_write(p, RMDR1, tmp);

	tmp = 0;
	tmp |= CTR_TSCKIZ_SCK | cpol << CTR_TSCKIZ_POL_SHIFT;
	tmp |= CTR_RSCKIZ_SCK | cpol << CTR_RSCKIZ_POL_SHIFT;

	edge = cpol ^ !cpha;

	tmp |= edge << CTR_TEDG_SHIFT;
	tmp |= edge << CTR_REDG_SHIFT;
	tmp |= tx_hi_z ? CTR_TXDIZ_HIZ : CTR_TXDIZ_LOW;
	sh_msiof_write(p, CTR, tmp);
}