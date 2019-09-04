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
struct xgbe_prv_data {unsigned long an_start; int kr_state; int kx_state; int /*<<< orphan*/  netdev; } ;
typedef  enum xgbe_rx { ____Placeholder_xgbe_rx } xgbe_rx ;
typedef  enum xgbe_an { ____Placeholder_xgbe_an } xgbe_an ;

/* Variables and functions */
 int XGBE_AN_ERROR ; 
 int /*<<< orphan*/  XGBE_AN_MS_TIMEOUT ; 
#define  XGBE_RX_BPA 129 
#define  XGBE_RX_XNP 128 
 void* jiffies ; 
 int /*<<< orphan*/  link ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ time_after (void*,unsigned long) ; 
 int xgbe_an73_rx_bpa (struct xgbe_prv_data*,int*) ; 
 int xgbe_an73_rx_xnp (struct xgbe_prv_data*,int*) ; 
 scalar_t__ xgbe_in_kr_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static enum xgbe_an xgbe_an73_page_received(struct xgbe_prv_data *pdata)
{
	enum xgbe_rx *state;
	unsigned long an_timeout;
	enum xgbe_an ret;

	if (!pdata->an_start) {
		pdata->an_start = jiffies;
	} else {
		an_timeout = pdata->an_start +
			     msecs_to_jiffies(XGBE_AN_MS_TIMEOUT);
		if (time_after(jiffies, an_timeout)) {
			/* Auto-negotiation timed out, reset state */
			pdata->kr_state = XGBE_RX_BPA;
			pdata->kx_state = XGBE_RX_BPA;

			pdata->an_start = jiffies;

			netif_dbg(pdata, link, pdata->netdev,
				  "CL73 AN timed out, resetting state\n");
		}
	}

	state = xgbe_in_kr_mode(pdata) ? &pdata->kr_state
				       : &pdata->kx_state;

	switch (*state) {
	case XGBE_RX_BPA:
		ret = xgbe_an73_rx_bpa(pdata, state);
		break;

	case XGBE_RX_XNP:
		ret = xgbe_an73_rx_xnp(pdata, state);
		break;

	default:
		ret = XGBE_AN_ERROR;
	}

	return ret;
}