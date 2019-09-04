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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct mtd_info {TYPE_1__ dev; } ;
struct bcm2835_smi_nand_host {struct bcm2835_smi_instance* smi_inst; } ;
struct bcm2835_smi_instance {int dummy; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_NCE ; 
 int SMI_NAND_ALE_PIN ; 
 int SMI_NAND_CLE_PIN ; 
 int /*<<< orphan*/  bcm2835_smi_set_address (struct bcm2835_smi_instance*,int) ; 
 int /*<<< orphan*/  bcm2835_smi_write_buf (struct bcm2835_smi_instance*,int*,int) ; 
 struct bcm2835_smi_nand_host* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bcm2835_smi_nand_cmd_ctrl(struct mtd_info *mtd, int cmd,
					     unsigned int ctrl)
{
	uint32_t cmd32 = cmd;
	uint32_t addr = ~(SMI_NAND_CLE_PIN | SMI_NAND_ALE_PIN);
	struct bcm2835_smi_nand_host *host = dev_get_drvdata(mtd->dev.parent);
	struct bcm2835_smi_instance *inst = host->smi_inst;

	if (ctrl & NAND_CLE)
		addr |= SMI_NAND_CLE_PIN;
	if (ctrl & NAND_ALE)
		addr |= SMI_NAND_ALE_PIN;
	/* Lower ALL the CS pins! */
	if (ctrl & NAND_NCE)
		addr &= (SMI_NAND_CLE_PIN | SMI_NAND_ALE_PIN);

	bcm2835_smi_set_address(inst, addr);

	if (cmd != NAND_CMD_NONE)
		bcm2835_smi_write_buf(inst, &cmd32, 1);
}