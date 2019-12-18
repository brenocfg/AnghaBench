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
struct ftmac100_txdes {int dummy; } ;
struct ftmac100 {size_t tx_clean_pointer; TYPE_1__* descs; } ;
struct TYPE_2__ {struct ftmac100_txdes* txdes; } ;

/* Variables and functions */

__attribute__((used)) static struct ftmac100_txdes *ftmac100_current_clean_txdes(struct ftmac100 *priv)
{
	return &priv->descs->txdes[priv->tx_clean_pointer];
}