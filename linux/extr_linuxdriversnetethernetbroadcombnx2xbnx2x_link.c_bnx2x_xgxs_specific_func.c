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
struct link_params {int port; struct bnx2x* bp; } ;
struct bnx2x_phy {int /*<<< orphan*/  def_md_devad; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIG_REG_XGXS0_CTRL_MD_DEVAD ; 
 int /*<<< orphan*/  NIG_REG_XGXS0_CTRL_MD_ST ; 
#define  PHY_INIT 128 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_xgxs_specific_func(struct bnx2x_phy *phy,
				     struct link_params *params,
				     u32 action)
{
	struct bnx2x *bp = params->bp;
	switch (action) {
	case PHY_INIT:
		/* Set correct devad */
		REG_WR(bp, NIG_REG_XGXS0_CTRL_MD_ST + params->port*0x18, 0);
		REG_WR(bp, NIG_REG_XGXS0_CTRL_MD_DEVAD + params->port*0x18,
		       phy->def_md_devad);
		break;
	}
}