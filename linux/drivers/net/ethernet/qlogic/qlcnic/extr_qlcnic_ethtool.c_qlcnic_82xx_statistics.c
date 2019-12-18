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
struct qlcnic_adapter {int drv_tx_rings; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int QLCNIC_TX_STATS_LEN ; 
 int /*<<< orphan*/  qlcnic_83xx_mac_stats_strings ; 
 int /*<<< orphan*/  qlcnic_gstrings_stats ; 

__attribute__((used)) static inline int qlcnic_82xx_statistics(struct qlcnic_adapter *adapter)
{
	return ARRAY_SIZE(qlcnic_gstrings_stats) +
	       ARRAY_SIZE(qlcnic_83xx_mac_stats_strings) +
	       QLCNIC_TX_STATS_LEN * adapter->drv_tx_rings;
}