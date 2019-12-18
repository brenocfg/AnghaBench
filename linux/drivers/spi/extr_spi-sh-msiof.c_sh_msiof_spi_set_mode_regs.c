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
 int MDR2_BITLEN1 (int) ; 
 int MDR2_GRPMASK1 ; 
 int MDR2_WDLEN1 (int) ; 
 int /*<<< orphan*/  RMDR2 ; 
 int SPI_CONTROLLER_MUST_TX ; 
 int /*<<< orphan*/  TMDR2 ; 
 int /*<<< orphan*/  sh_msiof_write (struct sh_msiof_spi_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sh_msiof_spi_set_mode_regs(struct sh_msiof_spi_priv *p,
				       const void *tx_buf, void *rx_buf,
				       u32 bits, u32 words)
{
	u32 dr2 = MDR2_BITLEN1(bits) | MDR2_WDLEN1(words);

	if (tx_buf || (p->ctlr->flags & SPI_CONTROLLER_MUST_TX))
		sh_msiof_write(p, TMDR2, dr2);
	else
		sh_msiof_write(p, TMDR2, dr2 | MDR2_GRPMASK1);

	if (rx_buf)
		sh_msiof_write(p, RMDR2, dr2);
}