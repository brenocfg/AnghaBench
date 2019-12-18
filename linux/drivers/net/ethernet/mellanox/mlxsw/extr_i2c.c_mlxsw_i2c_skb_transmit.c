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
struct sk_buff {int dummy; } ;
struct mlxsw_tx_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int mlxsw_i2c_skb_transmit(void *bus_priv, struct sk_buff *skb,
				  const struct mlxsw_tx_info *tx_info)
{
	return 0;
}