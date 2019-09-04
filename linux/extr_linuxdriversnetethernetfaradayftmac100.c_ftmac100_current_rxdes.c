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
struct ftmac100_rxdes {int dummy; } ;
struct ftmac100 {size_t rx_pointer; TYPE_1__* descs; } ;
struct TYPE_2__ {struct ftmac100_rxdes* rxdes; } ;

/* Variables and functions */

__attribute__((used)) static struct ftmac100_rxdes *ftmac100_current_rxdes(struct ftmac100 *priv)
{
	return &priv->descs->rxdes[priv->rx_pointer];
}