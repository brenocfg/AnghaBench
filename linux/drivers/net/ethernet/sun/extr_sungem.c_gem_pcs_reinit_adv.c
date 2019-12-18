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
struct gem {scalar_t__ phy_type; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ PCS_CFG ; 
 int PCS_CFG_ENABLE ; 
 int PCS_CFG_TO ; 
 scalar_t__ PCS_MIIADV ; 
 int PCS_MIIADV_AP ; 
 int PCS_MIIADV_FD ; 
 int PCS_MIIADV_HD ; 
 int PCS_MIIADV_SP ; 
 scalar_t__ PCS_MIICTRL ; 
 int PCS_MIICTRL_ANE ; 
 int PCS_MIICTRL_RAN ; 
 int PCS_MIICTRL_WB ; 
 scalar_t__ PCS_SCTRL ; 
 int PCS_SCTRL_LOOP ; 
 scalar_t__ phy_serialink ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gem_pcs_reinit_adv(struct gem *gp)
{
	u32 val;

	/* Make sure PCS is disabled while changing advertisement
	 * configuration.
	 */
	val = readl(gp->regs + PCS_CFG);
	val &= ~(PCS_CFG_ENABLE | PCS_CFG_TO);
	writel(val, gp->regs + PCS_CFG);

	/* Advertise all capabilities except asymmetric
	 * pause.
	 */
	val = readl(gp->regs + PCS_MIIADV);
	val |= (PCS_MIIADV_FD | PCS_MIIADV_HD |
		PCS_MIIADV_SP | PCS_MIIADV_AP);
	writel(val, gp->regs + PCS_MIIADV);

	/* Enable and restart auto-negotiation, disable wrapback/loopback,
	 * and re-enable PCS.
	 */
	val = readl(gp->regs + PCS_MIICTRL);
	val |= (PCS_MIICTRL_RAN | PCS_MIICTRL_ANE);
	val &= ~PCS_MIICTRL_WB;
	writel(val, gp->regs + PCS_MIICTRL);

	val = readl(gp->regs + PCS_CFG);
	val |= PCS_CFG_ENABLE;
	writel(val, gp->regs + PCS_CFG);

	/* Make sure serialink loopback is off.  The meaning
	 * of this bit is logically inverted based upon whether
	 * you are in Serialink or SERDES mode.
	 */
	val = readl(gp->regs + PCS_SCTRL);
	if (gp->phy_type == phy_serialink)
		val &= ~PCS_SCTRL_LOOP;
	else
		val |= PCS_SCTRL_LOOP;
	writel(val, gp->regs + PCS_SCTRL);
}