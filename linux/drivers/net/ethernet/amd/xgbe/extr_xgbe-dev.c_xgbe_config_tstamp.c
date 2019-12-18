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
struct xgbe_prv_data {int /*<<< orphan*/  tstamp_cc; int /*<<< orphan*/  tstamp_tc; int /*<<< orphan*/  tstamp_addend; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_SSIR ; 
 int /*<<< orphan*/  MAC_TSCR ; 
 int /*<<< orphan*/  SNSINC ; 
 int /*<<< orphan*/  SSINC ; 
 int /*<<< orphan*/  TSCFUPDT ; 
 int /*<<< orphan*/  TSCTRLSSR ; 
 int /*<<< orphan*/  TSENA ; 
 int /*<<< orphan*/  TXTSSTSM ; 
 int /*<<< orphan*/  XGBE_TSTAMP_SNSINC ; 
 int /*<<< orphan*/  XGBE_TSTAMP_SSINC ; 
 int /*<<< orphan*/  XGMAC_GET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_set_tstamp_time (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_update_tstamp_addend (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgbe_config_tstamp(struct xgbe_prv_data *pdata,
			      unsigned int mac_tscr)
{
	/* Set one nano-second accuracy */
	XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSCTRLSSR, 1);

	/* Set fine timestamp update */
	XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSCFUPDT, 1);

	/* Overwrite earlier timestamps */
	XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TXTSSTSM, 1);

	XGMAC_IOWRITE(pdata, MAC_TSCR, mac_tscr);

	/* Exit if timestamping is not enabled */
	if (!XGMAC_GET_BITS(mac_tscr, MAC_TSCR, TSENA))
		return 0;

	/* Initialize time registers */
	XGMAC_IOWRITE_BITS(pdata, MAC_SSIR, SSINC, XGBE_TSTAMP_SSINC);
	XGMAC_IOWRITE_BITS(pdata, MAC_SSIR, SNSINC, XGBE_TSTAMP_SNSINC);
	xgbe_update_tstamp_addend(pdata, pdata->tstamp_addend);
	xgbe_set_tstamp_time(pdata, 0, 0);

	/* Initialize the timecounter */
	timecounter_init(&pdata->tstamp_tc, &pdata->tstamp_cc,
			 ktime_to_ns(ktime_get_real()));

	return 0;
}