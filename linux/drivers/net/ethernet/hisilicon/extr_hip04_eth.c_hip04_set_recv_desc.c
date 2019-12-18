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
typedef  int u32 ;
struct hip04_priv {int port; int /*<<< orphan*/  map; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int PPE_BUF_SIZE_SHIFT ; 
 scalar_t__ PPE_CFG_RX_ADDR ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void hip04_set_recv_desc(struct hip04_priv *priv, dma_addr_t phys)
{
	u32 val;

	val = phys >> PPE_BUF_SIZE_SHIFT;
	regmap_write(priv->map, priv->port * 4 + PPE_CFG_RX_ADDR, val);
}