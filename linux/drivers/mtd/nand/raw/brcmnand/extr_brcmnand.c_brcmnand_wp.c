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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct brcmnand_host {TYPE_1__* pdev; struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {int features; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BRCMNAND_HAS_WP ; 
 int NAND_CTRL_RDY ; 
 int NAND_STATUS_READY ; 
 int NAND_STATUS_WP ; 
 int bcmnand_ctrl_poll_status (struct brcmnand_controller*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmnand_set_wp (struct brcmnand_controller*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*,char*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_status_op (struct nand_chip*,int /*<<< orphan*/ *) ; 
 int wp_on ; 

__attribute__((used)) static void brcmnand_wp(struct mtd_info *mtd, int wp)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct brcmnand_host *host = nand_get_controller_data(chip);
	struct brcmnand_controller *ctrl = host->ctrl;

	if ((ctrl->features & BRCMNAND_HAS_WP) && wp_on == 1) {
		static int old_wp = -1;
		int ret;

		if (old_wp != wp) {
			dev_dbg(ctrl->dev, "WP %s\n", wp ? "on" : "off");
			old_wp = wp;
		}

		/*
		 * make sure ctrl/flash ready before and after
		 * changing state of #WP pin
		 */
		ret = bcmnand_ctrl_poll_status(ctrl, NAND_CTRL_RDY |
					       NAND_STATUS_READY,
					       NAND_CTRL_RDY |
					       NAND_STATUS_READY, 0);
		if (ret)
			return;

		brcmnand_set_wp(ctrl, wp);
		nand_status_op(chip, NULL);
		/* NAND_STATUS_WP 0x00 = protected, 0x80 = not protected */
		ret = bcmnand_ctrl_poll_status(ctrl,
					       NAND_CTRL_RDY |
					       NAND_STATUS_READY |
					       NAND_STATUS_WP,
					       NAND_CTRL_RDY |
					       NAND_STATUS_READY |
					       (wp ? 0 : NAND_STATUS_WP), 0);

		if (ret)
			dev_err_ratelimited(&host->pdev->dev,
					    "nand #WP expected %s\n",
					    wp ? "on" : "off");
	}
}