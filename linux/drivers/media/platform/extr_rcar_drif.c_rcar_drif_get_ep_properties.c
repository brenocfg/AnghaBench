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
typedef  scalar_t__ u32 ;
struct rcar_drif_sdr {int mdr1; int /*<<< orphan*/  dev; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int RCAR_DRIF_SIRMDR1_DTDL_1 ; 
 int RCAR_DRIF_SIRMDR1_MSB_FIRST ; 
 int RCAR_DRIF_SIRMDR1_SYNCAC_POL_HIGH ; 
 int RCAR_DRIF_SIRMDR1_SYNCAC_POL_LOW ; 
 int RCAR_DRIF_SIRMDR1_SYNCDL_0 ; 
 int RCAR_DRIF_SIRMDR1_SYNCMD_LR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fwnode_property_read_u32 (struct fwnode_handle*,char*,scalar_t__*) ; 

__attribute__((used)) static void rcar_drif_get_ep_properties(struct rcar_drif_sdr *sdr,
					struct fwnode_handle *fwnode)
{
	u32 val;

	/* Set the I2S defaults for SIRMDR1*/
	sdr->mdr1 = RCAR_DRIF_SIRMDR1_SYNCMD_LR | RCAR_DRIF_SIRMDR1_MSB_FIRST |
		RCAR_DRIF_SIRMDR1_DTDL_1 | RCAR_DRIF_SIRMDR1_SYNCDL_0;

	/* Parse sync polarity from endpoint */
	if (!fwnode_property_read_u32(fwnode, "sync-active", &val))
		sdr->mdr1 |= val ? RCAR_DRIF_SIRMDR1_SYNCAC_POL_HIGH :
			RCAR_DRIF_SIRMDR1_SYNCAC_POL_LOW;
	else
		sdr->mdr1 |= RCAR_DRIF_SIRMDR1_SYNCAC_POL_HIGH; /* default */

	dev_dbg(sdr->dev, "mdr1 0x%08x\n", sdr->mdr1);
}