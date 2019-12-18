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
typedef  int /*<<< orphan*/  u8 ;
struct serdes_macro {int port; struct serdes_ctrl* ctrl; int /*<<< orphan*/  idx; } ;
struct serdes_ctrl {int /*<<< orphan*/  dev; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 struct serdes_macro* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,struct serdes_macro*) ; 
 int /*<<< orphan*/  serdes_ops ; 

__attribute__((used)) static int serdes_phy_create(struct serdes_ctrl *ctrl, u8 idx, struct phy **phy)
{
	struct serdes_macro *macro;

	*phy = devm_phy_create(ctrl->dev, NULL, &serdes_ops);
	if (IS_ERR(*phy))
		return PTR_ERR(*phy);

	macro = devm_kzalloc(ctrl->dev, sizeof(*macro), GFP_KERNEL);
	if (!macro)
		return -ENOMEM;

	macro->idx = idx;
	macro->ctrl = ctrl;
	macro->port = -1;

	phy_set_drvdata(*phy, macro);

	return 0;
}