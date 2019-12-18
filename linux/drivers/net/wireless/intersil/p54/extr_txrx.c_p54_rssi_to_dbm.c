#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct p54_common {int rxhw; TYPE_1__* cur_rssi; } ;
struct TYPE_2__ {int mul; int add; } ;

/* Variables and functions */

__attribute__((used)) static int p54_rssi_to_dbm(struct p54_common *priv, int rssi)
{
	if (priv->rxhw != 5) {
		return ((rssi * priv->cur_rssi->mul) / 64 +
			 priv->cur_rssi->add) / 4;
	} else {
		/*
		 * TODO: find the correct formula
		 */
		return rssi / 2 - 110;
	}
}