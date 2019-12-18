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
struct ftgmac100 {scalar_t__ tx_pointer; scalar_t__ tx_clean_pointer; } ;

/* Variables and functions */

__attribute__((used)) static bool ftgmac100_tx_buf_cleanable(struct ftgmac100 *priv)
{
	return priv->tx_pointer != priv->tx_clean_pointer;
}