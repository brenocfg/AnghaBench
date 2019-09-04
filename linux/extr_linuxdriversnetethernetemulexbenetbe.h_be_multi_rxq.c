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
struct be_adapter {int num_rx_qs; } ;

/* Variables and functions */

__attribute__((used)) static inline bool be_multi_rxq(const struct be_adapter *adapter)
{
	return adapter->num_rx_qs > 1;
}