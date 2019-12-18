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
struct npcm_pspi {int id; int /*<<< orphan*/  rst_regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPCM7XX_IPSRST2_OFFSET ; 
 int NPCM7XX_PSPI1_RESET ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void npcm_pspi_reset_hw(struct npcm_pspi *priv)
{
	regmap_write(priv->rst_regmap, NPCM7XX_IPSRST2_OFFSET,
		     NPCM7XX_PSPI1_RESET << priv->id);
	regmap_write(priv->rst_regmap, NPCM7XX_IPSRST2_OFFSET, 0x0);
}