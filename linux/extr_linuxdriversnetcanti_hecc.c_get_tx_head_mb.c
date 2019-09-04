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
struct ti_hecc_priv {int tx_head; } ;

/* Variables and functions */
 int HECC_TX_MB_MASK ; 

__attribute__((used)) static inline int get_tx_head_mb(struct ti_hecc_priv *priv)
{
	return priv->tx_head & HECC_TX_MB_MASK;
}