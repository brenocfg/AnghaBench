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
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct crb_priv {TYPE_1__* regs_t; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_DRV_STS_COMPLETE ; 
 int CRB_START_INVOKE ; 
 struct crb_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 crb_status(struct tpm_chip *chip)
{
	struct crb_priv *priv = dev_get_drvdata(&chip->dev);
	u8 sts = 0;

	if ((ioread32(&priv->regs_t->ctrl_start) & CRB_START_INVOKE) !=
	    CRB_START_INVOKE)
		sts |= CRB_DRV_STS_COMPLETE;

	return sts;
}