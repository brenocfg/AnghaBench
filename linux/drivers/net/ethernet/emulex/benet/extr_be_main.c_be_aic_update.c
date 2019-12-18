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
typedef  int /*<<< orphan*/  ulong ;
typedef  void* u64 ;
struct be_aic_obj {int /*<<< orphan*/  jiffies; void* tx_reqs_prev; void* rx_pkts_prev; } ;

/* Variables and functions */

__attribute__((used)) static void be_aic_update(struct be_aic_obj *aic, u64 rx_pkts, u64 tx_pkts,
			  ulong now)
{
	aic->rx_pkts_prev = rx_pkts;
	aic->tx_reqs_prev = tx_pkts;
	aic->jiffies = now;
}