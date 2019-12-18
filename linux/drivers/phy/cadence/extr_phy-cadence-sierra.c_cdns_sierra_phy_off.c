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
struct phy {int dummy; } ;
struct cdns_sierra_inst {int /*<<< orphan*/  lnk_rst; } ;

/* Variables and functions */
 struct cdns_sierra_inst* phy_get_drvdata (struct phy*) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns_sierra_phy_off(struct phy *gphy)
{
	struct cdns_sierra_inst *ins = phy_get_drvdata(gphy);

	return reset_control_assert(ins->lnk_rst);
}