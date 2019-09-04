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
struct ena_adapter {int tx_frames; int rx_frames; scalar_t__ rx_usecs; scalar_t__ tx_usecs; } ;

/* Variables and functions */

__attribute__((used)) static void ena_restore_ethtool_params(struct ena_adapter *adapter)
{
	adapter->tx_usecs = 0;
	adapter->rx_usecs = 0;
	adapter->tx_frames = 1;
	adapter->rx_frames = 1;
}