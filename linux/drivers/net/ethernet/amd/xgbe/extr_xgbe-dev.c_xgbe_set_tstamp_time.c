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
struct xgbe_prv_data {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_STNUR ; 
 int /*<<< orphan*/  MAC_STSUR ; 
 int /*<<< orphan*/  MAC_TSCR ; 
 int /*<<< orphan*/  TSINIT ; 
 scalar_t__ XGMAC_IOREAD_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void xgbe_set_tstamp_time(struct xgbe_prv_data *pdata, unsigned int sec,
				 unsigned int nsec)
{
	unsigned int count = 10000;

	/* Set the time values and tell the device */
	XGMAC_IOWRITE(pdata, MAC_STSUR, sec);
	XGMAC_IOWRITE(pdata, MAC_STNUR, nsec);
	XGMAC_IOWRITE_BITS(pdata, MAC_TSCR, TSINIT, 1);

	/* Wait for time update to complete */
	while (--count && XGMAC_IOREAD_BITS(pdata, MAC_TSCR, TSINIT))
		udelay(5);

	if (!count)
		netdev_err(pdata->netdev, "timed out initializing timestamp\n");
}