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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_filter; int /*<<< orphan*/  tx_type; } ;
struct cyclecounter {int mult; scalar_t__ shift; int /*<<< orphan*/  mask; int /*<<< orphan*/  read; } ;
struct ptp_clock_info {int /*<<< orphan*/  enable; int /*<<< orphan*/  settime64; int /*<<< orphan*/  gettime64; int /*<<< orphan*/  adjtime; int /*<<< orphan*/  adjfreq; int /*<<< orphan*/  max_adj; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct xgbe_prv_data {TYPE_1__ tstamp_config; struct cyclecounter tstamp_cc; int /*<<< orphan*/  tstamp_tc; int /*<<< orphan*/  ptpclk_rate; int /*<<< orphan*/  tstamp_addend; struct ptp_clock* ptp_clock; int /*<<< orphan*/  dev; int /*<<< orphan*/  netdev; struct ptp_clock_info ptp_clock_info; } ;
struct ptp_clock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCKSOURCE_MASK (int) ; 
 int /*<<< orphan*/  HWTSTAMP_FILTER_NONE ; 
 int /*<<< orphan*/  HWTSTAMP_TX_OFF ; 
 scalar_t__ IS_ERR (struct ptp_clock*) ; 
 int /*<<< orphan*/  MAC_TSCR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  XGMAC_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  div_u64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 char* netdev_name (int /*<<< orphan*/ ) ; 
 struct ptp_clock* ptp_clock_register (struct ptp_clock_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,struct cyclecounter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_adjfreq ; 
 int /*<<< orphan*/  xgbe_adjtime ; 
 int /*<<< orphan*/  xgbe_cc_read ; 
 int /*<<< orphan*/  xgbe_enable ; 
 int /*<<< orphan*/  xgbe_gettime ; 
 int /*<<< orphan*/  xgbe_settime ; 

void xgbe_ptp_register(struct xgbe_prv_data *pdata)
{
	struct ptp_clock_info *info = &pdata->ptp_clock_info;
	struct ptp_clock *clock;
	struct cyclecounter *cc = &pdata->tstamp_cc;
	u64 dividend;

	snprintf(info->name, sizeof(info->name), "%s",
		 netdev_name(pdata->netdev));
	info->owner = THIS_MODULE;
	info->max_adj = pdata->ptpclk_rate;
	info->adjfreq = xgbe_adjfreq;
	info->adjtime = xgbe_adjtime;
	info->gettime64 = xgbe_gettime;
	info->settime64 = xgbe_settime;
	info->enable = xgbe_enable;

	clock = ptp_clock_register(info, pdata->dev);
	if (IS_ERR(clock)) {
		dev_err(pdata->dev, "ptp_clock_register failed\n");
		return;
	}

	pdata->ptp_clock = clock;

	/* Calculate the addend:
	 *   addend = 2^32 / (PTP ref clock / 50Mhz)
	 *          = (2^32 * 50Mhz) / PTP ref clock
	 */
	dividend = 50000000;
	dividend <<= 32;
	pdata->tstamp_addend = div_u64(dividend, pdata->ptpclk_rate);

	/* Setup the timecounter */
	cc->read = xgbe_cc_read;
	cc->mask = CLOCKSOURCE_MASK(64);
	cc->mult = 1;
	cc->shift = 0;

	timecounter_init(&pdata->tstamp_tc, &pdata->tstamp_cc,
			 ktime_to_ns(ktime_get_real()));

	/* Disable all timestamping to start */
	XGMAC_IOWRITE(pdata, MAC_TSCR, 0);
	pdata->tstamp_config.tx_type = HWTSTAMP_TX_OFF;
	pdata->tstamp_config.rx_filter = HWTSTAMP_FILTER_NONE;
}