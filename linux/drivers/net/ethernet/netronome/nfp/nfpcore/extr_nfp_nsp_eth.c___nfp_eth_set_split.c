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

/* Variables and functions */
 int NFP_ETH_SET_BIT_CONFIG (struct nfp_nsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSP_ETH_CTRL_SET_LANES ; 
 int /*<<< orphan*/  NSP_ETH_PORT_LANES ; 
 int /*<<< orphan*/  NSP_ETH_RAW_PORT ; 

int __nfp_eth_set_split(struct nfp_nsp *nsp, unsigned int lanes)
{
	return NFP_ETH_SET_BIT_CONFIG(nsp, NSP_ETH_RAW_PORT, NSP_ETH_PORT_LANES,
				      lanes, NSP_ETH_CTRL_SET_LANES);
}