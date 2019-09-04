#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * cmd; } ;
struct ocrdma_mqe {TYPE_1__ u; } ;
struct ocrdma_mbx_hdr {int dummy; } ;
struct ocrdma_get_phy_info_rsp {int ityp_ptyp; int fspeed_aspeed; } ;
struct TYPE_4__ {int phy_type; int interface_type; int auto_speeds_supported; int fixed_speeds_supported; } ;
struct ocrdma_dev {TYPE_2__ phy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int OCRDMA_ASPEED_SUPP_MASK ; 
 int /*<<< orphan*/  OCRDMA_CMD_PHY_DETAILS ; 
 int OCRDMA_FSPEED_SUPP_MASK ; 
 int OCRDMA_FSPEED_SUPP_SHIFT ; 
 int OCRDMA_IF_TYPE_MASK ; 
 int OCRDMA_IF_TYPE_SHIFT ; 
 int OCRDMA_PHY_TYPE_MASK ; 
 int /*<<< orphan*/  OCRDMA_SUBSYS_COMMON ; 
 int /*<<< orphan*/  kfree (struct ocrdma_mqe*) ; 
 struct ocrdma_mqe* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_init_mch (struct ocrdma_mbx_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ocrdma_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*) ; 

__attribute__((used)) static int ocrdma_mbx_get_phy_info(struct ocrdma_dev *dev)
{
	int status = -ENOMEM;
	struct ocrdma_mqe *cmd;
	struct ocrdma_get_phy_info_rsp *rsp;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_PHY_DETAILS, sizeof(*cmd));
	if (!cmd)
		return status;

	ocrdma_init_mch((struct ocrdma_mbx_hdr *)&cmd->u.cmd[0],
			OCRDMA_CMD_PHY_DETAILS, OCRDMA_SUBSYS_COMMON,
			sizeof(*cmd));

	status = ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	if (status)
		goto mbx_err;

	rsp = (struct ocrdma_get_phy_info_rsp *)cmd;
	dev->phy.phy_type =
			(rsp->ityp_ptyp & OCRDMA_PHY_TYPE_MASK);
	dev->phy.interface_type =
			(rsp->ityp_ptyp & OCRDMA_IF_TYPE_MASK)
				>> OCRDMA_IF_TYPE_SHIFT;
	dev->phy.auto_speeds_supported  =
			(rsp->fspeed_aspeed & OCRDMA_ASPEED_SUPP_MASK);
	dev->phy.fixed_speeds_supported =
			(rsp->fspeed_aspeed & OCRDMA_FSPEED_SUPP_MASK)
				>> OCRDMA_FSPEED_SUPP_SHIFT;
mbx_err:
	kfree(cmd);
	return status;
}