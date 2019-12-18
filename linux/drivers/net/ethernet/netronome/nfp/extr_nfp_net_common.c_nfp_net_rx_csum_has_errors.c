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
typedef  int u16 ;

/* Variables and functions */
 int PCIE_DESC_RX_CSUM_OK_SHIFT ; 
 int __PCIE_DESC_RX_CSUM_ALL ; 
 int __PCIE_DESC_RX_CSUM_ALL_OK ; 

__attribute__((used)) static int nfp_net_rx_csum_has_errors(u16 flags)
{
	u16 csum_all_checked, csum_all_ok;

	csum_all_checked = flags & __PCIE_DESC_RX_CSUM_ALL;
	csum_all_ok = flags & __PCIE_DESC_RX_CSUM_ALL_OK;

	return csum_all_checked != (csum_all_ok << PCIE_DESC_RX_CSUM_OK_SHIFT);
}