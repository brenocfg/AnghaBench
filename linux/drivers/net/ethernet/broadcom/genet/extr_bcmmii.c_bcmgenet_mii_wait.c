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
struct bcmgenet_priv {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int HZ ; 
 int MDIO_START_BUSY ; 
 int /*<<< orphan*/  UMAC_MDIO_CMD ; 
 int bcmgenet_umac_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int bcmgenet_mii_wait(void *wait_func_data)
{
	struct bcmgenet_priv *priv = wait_func_data;

	wait_event_timeout(priv->wq,
			   !(bcmgenet_umac_readl(priv, UMAC_MDIO_CMD)
			   & MDIO_START_BUSY),
			   HZ / 100);
	return 0;
}