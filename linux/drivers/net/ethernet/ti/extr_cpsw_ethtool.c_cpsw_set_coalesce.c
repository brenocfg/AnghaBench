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
struct net_device {int dummy; } ;
struct ethtool_coalesce {int rx_coalesce_usecs; } ;
struct cpsw_priv {struct cpsw_common* cpsw; } ;
struct cpsw_common {int bus_freq_mhz; int coal_intvl; TYPE_1__* wr_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_control; int /*<<< orphan*/  tx_imax; int /*<<< orphan*/  rx_imax; } ;

/* Variables and functions */
 int CPSW_CMINTMAX_INTVL ; 
 int CPSW_CMINTMIN_INTVL ; 
 int CPSW_INTPACEEN ; 
 int CPSW_INTPRESCALE_MASK ; 
 int /*<<< orphan*/  cpsw_notice (struct cpsw_priv*,int /*<<< orphan*/ ,char*,int) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

int cpsw_set_coalesce(struct net_device *ndev, struct ethtool_coalesce *coal)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	u32 int_ctrl;
	u32 num_interrupts = 0;
	u32 prescale = 0;
	u32 addnl_dvdr = 1;
	u32 coal_intvl = 0;
	struct cpsw_common *cpsw = priv->cpsw;

	coal_intvl = coal->rx_coalesce_usecs;

	int_ctrl =  readl(&cpsw->wr_regs->int_control);
	prescale = cpsw->bus_freq_mhz * 4;

	if (!coal->rx_coalesce_usecs) {
		int_ctrl &= ~(CPSW_INTPRESCALE_MASK | CPSW_INTPACEEN);
		goto update_return;
	}

	if (coal_intvl < CPSW_CMINTMIN_INTVL)
		coal_intvl = CPSW_CMINTMIN_INTVL;

	if (coal_intvl > CPSW_CMINTMAX_INTVL) {
		/* Interrupt pacer works with 4us Pulse, we can
		 * throttle further by dilating the 4us pulse.
		 */
		addnl_dvdr = CPSW_INTPRESCALE_MASK / prescale;

		if (addnl_dvdr > 1) {
			prescale *= addnl_dvdr;
			if (coal_intvl > (CPSW_CMINTMAX_INTVL * addnl_dvdr))
				coal_intvl = (CPSW_CMINTMAX_INTVL
						* addnl_dvdr);
		} else {
			addnl_dvdr = 1;
			coal_intvl = CPSW_CMINTMAX_INTVL;
		}
	}

	num_interrupts = (1000 * addnl_dvdr) / coal_intvl;
	writel(num_interrupts, &cpsw->wr_regs->rx_imax);
	writel(num_interrupts, &cpsw->wr_regs->tx_imax);

	int_ctrl |= CPSW_INTPACEEN;
	int_ctrl &= (~CPSW_INTPRESCALE_MASK);
	int_ctrl |= (prescale & CPSW_INTPRESCALE_MASK);

update_return:
	writel(int_ctrl, &cpsw->wr_regs->int_control);

	cpsw_notice(priv, timer, "Set coalesce to %d usecs.\n", coal_intvl);
	cpsw->coal_intvl = coal_intvl;

	return 0;
}