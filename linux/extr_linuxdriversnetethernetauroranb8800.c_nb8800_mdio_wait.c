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
struct nb8800_priv {scalar_t__ base; } ;
struct mii_bus {struct nb8800_priv* priv; } ;

/* Variables and functions */
 int MDIO_CMD_GO ; 
 scalar_t__ NB8800_MDIO_CMD ; 
 int readl_poll_timeout_atomic (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static int nb8800_mdio_wait(struct mii_bus *bus)
{
	struct nb8800_priv *priv = bus->priv;
	u32 val;

	return readl_poll_timeout_atomic(priv->base + NB8800_MDIO_CMD,
					 val, !(val & MDIO_CMD_GO), 1, 1000);
}