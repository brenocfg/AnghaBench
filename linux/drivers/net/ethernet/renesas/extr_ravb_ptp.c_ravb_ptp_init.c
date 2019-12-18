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
struct TYPE_2__ {int /*<<< orphan*/  info; int /*<<< orphan*/  clock; int /*<<< orphan*/  default_addend; int /*<<< orphan*/  current_addend; } ;
struct ravb_private {TYPE_1__ ptp; int /*<<< orphan*/  lock; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCCR ; 
 int /*<<< orphan*/  GCCR_TCR ; 
 int /*<<< orphan*/  GCCR_TCR_NOREQ ; 
 int /*<<< orphan*/  GCCR_TCSS ; 
 int /*<<< orphan*/  GCCR_TCSS_ADJGPTP ; 
 int /*<<< orphan*/  GTI ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ptp_clock_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_ptp_info ; 
 int /*<<< orphan*/  ravb_read (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_wait (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ravb_ptp_init(struct net_device *ndev, struct platform_device *pdev)
{
	struct ravb_private *priv = netdev_priv(ndev);
	unsigned long flags;

	priv->ptp.info = ravb_ptp_info;

	priv->ptp.default_addend = ravb_read(ndev, GTI);
	priv->ptp.current_addend = priv->ptp.default_addend;

	spin_lock_irqsave(&priv->lock, flags);
	ravb_wait(ndev, GCCR, GCCR_TCR, GCCR_TCR_NOREQ);
	ravb_modify(ndev, GCCR, GCCR_TCSS, GCCR_TCSS_ADJGPTP);
	spin_unlock_irqrestore(&priv->lock, flags);

	priv->ptp.clock = ptp_clock_register(&priv->ptp.info, &pdev->dev);
}