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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct enc28j60_net {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERDPTL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nolock_regw_write (struct enc28j60_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_read_buf (struct enc28j60_net*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enc28j60_mem_read(struct enc28j60_net *priv,
				     u16 addr, int len, u8 *data)
{
	mutex_lock(&priv->lock);
	nolock_regw_write(priv, ERDPTL, addr);
#ifdef CONFIG_ENC28J60_WRITEVERIFY
	if (netif_msg_drv(priv)) {
		u16 reg;
		reg = nolock_regw_read(priv, ERDPTL);
		if (reg != addr)
			printk(KERN_DEBUG DRV_NAME ": %s() error writing ERDPT "
				"(0x%04x - 0x%04x)\n", __func__, reg, addr);
	}
#endif
	spi_read_buf(priv, len, data);
	mutex_unlock(&priv->lock);
}