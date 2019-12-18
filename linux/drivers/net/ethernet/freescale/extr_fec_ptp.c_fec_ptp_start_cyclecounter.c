#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {int shift; int /*<<< orphan*/  mult; int /*<<< orphan*/  mask; int /*<<< orphan*/  read; } ;
struct fec_enet_private {int cycle_speed; int /*<<< orphan*/  tmreg_lock; TYPE_1__ cc; int /*<<< orphan*/  tc; scalar_t__ hwp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCKSOURCE_MASK (int) ; 
 scalar_t__ FEC_ATIME_CTRL ; 
 scalar_t__ FEC_ATIME_EVT_PERIOD ; 
 scalar_t__ FEC_ATIME_INC ; 
 int /*<<< orphan*/  FEC_CC_MULT ; 
 int FEC_COUNTER_PERIOD ; 
 int FEC_T_CTRL_ENABLE ; 
 int FEC_T_CTRL_PERIOD_RST ; 
 int FEC_T_INC_OFFSET ; 
 int /*<<< orphan*/  fec_ptp_read ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void fec_ptp_start_cyclecounter(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	unsigned long flags;
	int inc;

	inc = 1000000000 / fep->cycle_speed;

	/* grab the ptp lock */
	spin_lock_irqsave(&fep->tmreg_lock, flags);

	/* 1ns counter */
	writel(inc << FEC_T_INC_OFFSET, fep->hwp + FEC_ATIME_INC);

	/* use 31-bit timer counter */
	writel(FEC_COUNTER_PERIOD, fep->hwp + FEC_ATIME_EVT_PERIOD);

	writel(FEC_T_CTRL_ENABLE | FEC_T_CTRL_PERIOD_RST,
		fep->hwp + FEC_ATIME_CTRL);

	memset(&fep->cc, 0, sizeof(fep->cc));
	fep->cc.read = fec_ptp_read;
	fep->cc.mask = CLOCKSOURCE_MASK(31);
	fep->cc.shift = 31;
	fep->cc.mult = FEC_CC_MULT;

	/* reset the ns time counter */
	timecounter_init(&fep->tc, &fep->cc, ktime_to_ns(ktime_get_real()));

	spin_unlock_irqrestore(&fep->tmreg_lock, flags);
}