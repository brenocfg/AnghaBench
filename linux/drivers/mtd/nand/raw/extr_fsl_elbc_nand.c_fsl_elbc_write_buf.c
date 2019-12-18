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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int dummy; } ;
struct mtd_info {unsigned int writesize; unsigned int oobsize; } ;
struct fsl_elbc_mtd {int /*<<< orphan*/  dev; TYPE_1__* ctrl; } ;
struct fsl_elbc_fcm_ctrl {unsigned int index; int /*<<< orphan*/ * addr; scalar_t__ status; } ;
struct TYPE_2__ {struct fsl_elbc_fcm_ctrl* nand; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  in_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 struct fsl_elbc_mtd* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void fsl_elbc_write_buf(struct nand_chip *chip, const u8 *buf, int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = priv->ctrl->nand;
	unsigned int bufsize = mtd->writesize + mtd->oobsize;

	if (len <= 0) {
		dev_err(priv->dev, "write_buf of %d bytes", len);
		elbc_fcm_ctrl->status = 0;
		return;
	}

	if ((unsigned int)len > bufsize - elbc_fcm_ctrl->index) {
		dev_err(priv->dev,
		        "write_buf beyond end of buffer "
		        "(%d requested, %u available)\n",
			len, bufsize - elbc_fcm_ctrl->index);
		len = bufsize - elbc_fcm_ctrl->index;
	}

	memcpy_toio(&elbc_fcm_ctrl->addr[elbc_fcm_ctrl->index], buf, len);
	/*
	 * This is workaround for the weird elbc hangs during nand write,
	 * Scott Wood says: "...perhaps difference in how long it takes a
	 * write to make it through the localbus compared to a write to IMMR
	 * is causing problems, and sync isn't helping for some reason."
	 * Reading back the last byte helps though.
	 */
	in_8(&elbc_fcm_ctrl->addr[elbc_fcm_ctrl->index] + len - 1);

	elbc_fcm_ctrl->index += len;
}