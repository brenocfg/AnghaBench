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
typedef  int u16 ;
struct npcm_pspi {scalar_t__ base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NPCM_PSPI_CTL1 ; 
 int NPCM_PSPI_CTL1_SCDV6_0 ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 

__attribute__((used)) static void npcm_pspi_set_baudrate(struct npcm_pspi *priv, unsigned int speed)
{
	u32 ckdiv;
	u16 regtemp;

	/* the supported rates are numbers from 4 to 256. */
	ckdiv = DIV_ROUND_CLOSEST(clk_get_rate(priv->clk), (2 * speed)) - 1;

	regtemp = ioread16(NPCM_PSPI_CTL1 + priv->base);
	regtemp &= ~NPCM_PSPI_CTL1_SCDV6_0;
	iowrite16(regtemp | (ckdiv << 9), NPCM_PSPI_CTL1 + priv->base);
}