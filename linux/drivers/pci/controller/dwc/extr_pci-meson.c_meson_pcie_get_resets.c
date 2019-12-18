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
struct meson_pcie_rc_reset {void* apb; void* port; void* phy; } ;
struct meson_pcie {struct meson_pcie_rc_reset mrst; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PCIE_NORMAL_RESET ; 
 int /*<<< orphan*/  PCIE_SHARED_RESET ; 
 int PTR_ERR (void*) ; 
 void* meson_pcie_get_reset (struct meson_pcie*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (void*) ; 

__attribute__((used)) static int meson_pcie_get_resets(struct meson_pcie *mp)
{
	struct meson_pcie_rc_reset *mrst = &mp->mrst;

	mrst->phy = meson_pcie_get_reset(mp, "phy", PCIE_SHARED_RESET);
	if (IS_ERR(mrst->phy))
		return PTR_ERR(mrst->phy);
	reset_control_deassert(mrst->phy);

	mrst->port = meson_pcie_get_reset(mp, "port", PCIE_NORMAL_RESET);
	if (IS_ERR(mrst->port))
		return PTR_ERR(mrst->port);
	reset_control_deassert(mrst->port);

	mrst->apb = meson_pcie_get_reset(mp, "apb", PCIE_SHARED_RESET);
	if (IS_ERR(mrst->apb))
		return PTR_ERR(mrst->apb);
	reset_control_deassert(mrst->apb);

	return 0;
}