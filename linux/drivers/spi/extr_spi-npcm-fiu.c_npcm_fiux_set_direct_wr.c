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
struct npcm_fiu_spi {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int DWR_ABPCK_4_BIT_PER_CLK ; 
 int DWR_DBPCK_4_BIT_PER_CLK ; 
 int /*<<< orphan*/  NPCM_FIU_DWR_16_BYTE_BURST ; 
 int NPCM_FIU_DWR_ABPCK_SHIFT ; 
 int /*<<< orphan*/  NPCM_FIU_DWR_CFG ; 
 int /*<<< orphan*/  NPCM_FIU_DWR_CFG_ABPCK ; 
 int /*<<< orphan*/  NPCM_FIU_DWR_CFG_DBPCK ; 
 int NPCM_FIU_DWR_DBPCK_SHIFT ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void npcm_fiux_set_direct_wr(struct npcm_fiu_spi *fiu)
{
	regmap_write(fiu->regmap, NPCM_FIU_DWR_CFG,
		     NPCM_FIU_DWR_16_BYTE_BURST);
	regmap_update_bits(fiu->regmap, NPCM_FIU_DWR_CFG,
			   NPCM_FIU_DWR_CFG_ABPCK,
			   DWR_ABPCK_4_BIT_PER_CLK << NPCM_FIU_DWR_ABPCK_SHIFT);
	regmap_update_bits(fiu->regmap, NPCM_FIU_DWR_CFG,
			   NPCM_FIU_DWR_CFG_DBPCK,
			   DWR_DBPCK_4_BIT_PER_CLK << NPCM_FIU_DWR_DBPCK_SHIFT);
}