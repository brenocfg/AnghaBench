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
struct net_device {int dummy; } ;
struct cc770_priv {int dummy; } ;

/* Variables and functions */
 int STAT_BOFF ; 
 int STAT_LEC_MASK ; 
 int STAT_WARN ; 
 int /*<<< orphan*/  cc770_err (struct net_device*,int) ; 
 int cc770_read_reg (struct cc770_priv*,int) ; 
 int /*<<< orphan*/  cc770_write_reg (struct cc770_priv*,int,int) ; 
 struct cc770_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int cc770_status_interrupt(struct net_device *dev)
{
	struct cc770_priv *priv = netdev_priv(dev);
	u8 status;

	status = cc770_read_reg(priv, status);
	/* Reset the status register including RXOK and TXOK */
	cc770_write_reg(priv, status, STAT_LEC_MASK);

	if (status & (STAT_WARN | STAT_BOFF) ||
	    (status & STAT_LEC_MASK) != STAT_LEC_MASK) {
		cc770_err(dev, status);
		return status & STAT_BOFF;
	}

	return 0;
}