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
typedef  enum nfp_eth_aneg { ____Placeholder_nfp_eth_aneg } nfp_eth_aneg ;

/* Variables and functions */
 int NFP_ETH_SET_BIT_CONFIG (struct nfp_nsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSP_ETH_CTRL_SET_ANEG ; 
 int /*<<< orphan*/  NSP_ETH_RAW_STATE ; 
 int /*<<< orphan*/  NSP_ETH_STATE_ANEG ; 

int __nfp_eth_set_aneg(struct nfp_nsp *nsp, enum nfp_eth_aneg mode)
{
	return NFP_ETH_SET_BIT_CONFIG(nsp, NSP_ETH_RAW_STATE,
				      NSP_ETH_STATE_ANEG, mode,
				      NSP_ETH_CTRL_SET_ANEG);
}