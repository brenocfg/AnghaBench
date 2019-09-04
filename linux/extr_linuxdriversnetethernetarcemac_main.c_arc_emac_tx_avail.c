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
struct arc_emac_priv {int txbd_dirty; int txbd_curr; } ;

/* Variables and functions */
 int TX_BD_NUM ; 

__attribute__((used)) static inline int arc_emac_tx_avail(struct arc_emac_priv *priv)
{
	return (priv->txbd_dirty + TX_BD_NUM - priv->txbd_curr - 1) % TX_BD_NUM;
}