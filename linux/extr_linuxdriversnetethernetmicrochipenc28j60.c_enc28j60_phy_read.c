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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct enc28j60_net {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICMD ; 
 int MICMD_MIIRD ; 
 int /*<<< orphan*/  MIRDL ; 
 int /*<<< orphan*/  MIREGADR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nolock_regb_write (struct enc28j60_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nolock_regw_read (struct enc28j60_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_phy_ready (struct enc28j60_net*) ; 

__attribute__((used)) static u16 enc28j60_phy_read(struct enc28j60_net *priv, u8 address)
{
	u16 ret;

	mutex_lock(&priv->lock);
	/* set the PHY register address */
	nolock_regb_write(priv, MIREGADR, address);
	/* start the register read operation */
	nolock_regb_write(priv, MICMD, MICMD_MIIRD);
	/* wait until the PHY read completes */
	wait_phy_ready(priv);
	/* quit reading */
	nolock_regb_write(priv, MICMD, 0x00);
	/* return the data */
	ret  = nolock_regw_read(priv, MIRDL);
	mutex_unlock(&priv->lock);

	return ret;
}