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
struct fsl_elbc_mtd {int /*<<< orphan*/  dev; TYPE_1__* ctrl; } ;
struct fsl_elbc_fcm_ctrl {size_t index; int /*<<< orphan*/ * addr; scalar_t__ read_bytes; } ;
struct TYPE_2__ {struct fsl_elbc_fcm_ctrl* nand; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (unsigned int,scalar_t__) ; 
 struct fsl_elbc_mtd* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void fsl_elbc_read_buf(struct nand_chip *chip, u8 *buf, int len)
{
	struct fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = priv->ctrl->nand;
	int avail;

	if (len < 0)
		return;

	avail = min((unsigned int)len,
			elbc_fcm_ctrl->read_bytes - elbc_fcm_ctrl->index);
	memcpy_fromio(buf, &elbc_fcm_ctrl->addr[elbc_fcm_ctrl->index], avail);
	elbc_fcm_ctrl->index += avail;

	if (len > avail)
		dev_err(priv->dev,
		        "read_buf beyond end of buffer "
		        "(%d requested, %d available)\n",
		        len, avail);
}