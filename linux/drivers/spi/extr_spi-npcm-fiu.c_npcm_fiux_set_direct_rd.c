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
struct npcm_fiu_spi {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int DRD_SPI_X_MODE ; 
 int /*<<< orphan*/  NPCM_FIU_DRD_16_BYTE_BURST ; 
 int NPCM_FIU_DRD_ACCTYPE_SHIFT ; 
 int /*<<< orphan*/  NPCM_FIU_DRD_CFG ; 
 int /*<<< orphan*/  NPCM_FIU_DRD_CFG_ACCTYPE ; 
 int /*<<< orphan*/  NPCM_FIU_DRD_CFG_DBW ; 
 int NPCM_FIU_DRD_DBW_SHIFT ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void npcm_fiux_set_direct_rd(struct npcm_fiu_spi *fiu)
{
	u32 rx_dummy = 0;

	regmap_write(fiu->regmap, NPCM_FIU_DRD_CFG,
		     NPCM_FIU_DRD_16_BYTE_BURST);
	regmap_update_bits(fiu->regmap, NPCM_FIU_DRD_CFG,
			   NPCM_FIU_DRD_CFG_ACCTYPE,
			   DRD_SPI_X_MODE << NPCM_FIU_DRD_ACCTYPE_SHIFT);
	regmap_update_bits(fiu->regmap, NPCM_FIU_DRD_CFG,
			   NPCM_FIU_DRD_CFG_DBW,
			   rx_dummy << NPCM_FIU_DRD_DBW_SHIFT);
}