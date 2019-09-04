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
struct nfp_nsp {int dummy; } ;
typedef  enum nfp_eth_rate { ____Placeholder_nfp_eth_rate } nfp_eth_rate ;

/* Variables and functions */
 int EINVAL ; 
 int NFP_ETH_SET_BIT_CONFIG (struct nfp_nsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSP_ETH_CTRL_SET_RATE ; 
 int /*<<< orphan*/  NSP_ETH_RAW_STATE ; 
 int /*<<< orphan*/  NSP_ETH_STATE_RATE ; 
 int RATE_INVALID ; 
 int nfp_eth_speed2rate (unsigned int) ; 
 int /*<<< orphan*/  nfp_nsp_cpp (struct nfp_nsp*) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 

int __nfp_eth_set_speed(struct nfp_nsp *nsp, unsigned int speed)
{
	enum nfp_eth_rate rate;

	rate = nfp_eth_speed2rate(speed);
	if (rate == RATE_INVALID) {
		nfp_warn(nfp_nsp_cpp(nsp),
			 "could not find matching lane rate for speed %u\n",
			 speed);
		return -EINVAL;
	}

	return NFP_ETH_SET_BIT_CONFIG(nsp, NSP_ETH_RAW_STATE,
				      NSP_ETH_STATE_RATE, rate,
				      NSP_ETH_CTRL_SET_RATE);
}