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
typedef  int u32 ;
typedef  int u16 ;
struct tlan_priv {int /*<<< orphan*/  lock; } ;
struct net_device {int base_addr; } ;

/* Variables and functions */
 int TLAN_DIO_ADR ; 
 int TLAN_DIO_DATA ; 
 int TLAN_NET_SIO ; 
 int /*<<< orphan*/  TLAN_NET_SIO_MCLK ; 
 int /*<<< orphan*/  TLAN_NET_SIO_MDATA ; 
 int /*<<< orphan*/  TLAN_NET_SIO_MINTEN ; 
 int /*<<< orphan*/  TLAN_NET_SIO_MTXEN ; 
 int /*<<< orphan*/  in_irq () ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tlan_clear_bit (int /*<<< orphan*/ ,int) ; 
 int tlan_get_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlan_mii_send_data (int,int,int) ; 
 int /*<<< orphan*/  tlan_mii_sync (int) ; 
 int /*<<< orphan*/  tlan_set_bit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
tlan_mii_read_reg(struct net_device *dev, u16 phy, u16 reg, u16 *val)
{
	u8	nack;
	u16	sio, tmp;
	u32	i;
	bool	err;
	int	minten;
	struct tlan_priv *priv = netdev_priv(dev);
	unsigned long flags = 0;

	err = false;
	outw(TLAN_NET_SIO, dev->base_addr + TLAN_DIO_ADR);
	sio = dev->base_addr + TLAN_DIO_DATA + TLAN_NET_SIO;

	if (!in_irq())
		spin_lock_irqsave(&priv->lock, flags);

	tlan_mii_sync(dev->base_addr);

	minten = tlan_get_bit(TLAN_NET_SIO_MINTEN, sio);
	if (minten)
		tlan_clear_bit(TLAN_NET_SIO_MINTEN, sio);

	tlan_mii_send_data(dev->base_addr, 0x1, 2);	/* start (01b) */
	tlan_mii_send_data(dev->base_addr, 0x2, 2);	/* read  (10b) */
	tlan_mii_send_data(dev->base_addr, phy, 5);	/* device #      */
	tlan_mii_send_data(dev->base_addr, reg, 5);	/* register #    */


	tlan_clear_bit(TLAN_NET_SIO_MTXEN, sio);	/* change direction */

	tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);		/* clock idle bit */
	tlan_set_bit(TLAN_NET_SIO_MCLK, sio);
	tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);		/* wait 300ns */

	nack = tlan_get_bit(TLAN_NET_SIO_MDATA, sio);	/* check for ACK */
	tlan_set_bit(TLAN_NET_SIO_MCLK, sio);		/* finish ACK */
	if (nack) {					/* no ACK, so fake it */
		for (i = 0; i < 16; i++) {
			tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);
			tlan_set_bit(TLAN_NET_SIO_MCLK, sio);
		}
		tmp = 0xffff;
		err = true;
	} else {					/* ACK, so read data */
		for (tmp = 0, i = 0x8000; i; i >>= 1) {
			tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);
			if (tlan_get_bit(TLAN_NET_SIO_MDATA, sio))
				tmp |= i;
			tlan_set_bit(TLAN_NET_SIO_MCLK, sio);
		}
	}


	tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);		/* idle cycle */
	tlan_set_bit(TLAN_NET_SIO_MCLK, sio);

	if (minten)
		tlan_set_bit(TLAN_NET_SIO_MINTEN, sio);

	*val = tmp;

	if (!in_irq())
		spin_unlock_irqrestore(&priv->lock, flags);

	return err;

}