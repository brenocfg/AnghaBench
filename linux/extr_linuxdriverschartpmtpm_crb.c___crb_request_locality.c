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
typedef  int u32 ;
struct device {int dummy; } ;
struct crb_priv {TYPE_1__* regs_h; } ;
struct TYPE_2__ {int /*<<< orphan*/  loc_state; int /*<<< orphan*/  loc_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_LOC_CTRL_REQUEST_ACCESS ; 
 int CRB_LOC_STATE_LOC_ASSIGNED ; 
 int CRB_LOC_STATE_TPM_REG_VALID_STS ; 
 int ETIME ; 
 int /*<<< orphan*/  TPM2_TIMEOUT_C ; 
 int /*<<< orphan*/  crb_wait_for_reg_32 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __crb_request_locality(struct device *dev,
				  struct crb_priv *priv, int loc)
{
	u32 value = CRB_LOC_STATE_LOC_ASSIGNED |
		    CRB_LOC_STATE_TPM_REG_VALID_STS;

	if (!priv->regs_h)
		return 0;

	iowrite32(CRB_LOC_CTRL_REQUEST_ACCESS, &priv->regs_h->loc_ctrl);
	if (!crb_wait_for_reg_32(&priv->regs_h->loc_state, value, value,
				 TPM2_TIMEOUT_C)) {
		dev_warn(dev, "TPM_LOC_STATE_x.requestAccess timed out\n");
		return -ETIME;
	}

	return 0;
}