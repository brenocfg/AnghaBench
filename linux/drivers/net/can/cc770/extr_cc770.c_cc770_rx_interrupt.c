#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct net_device_stats {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct cc770_priv {int control_normal_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl1; int /*<<< orphan*/  ctrl0; } ;

/* Variables and functions */
 int CC770_MAX_MSG ; 
 int CTRL_EAF ; 
 int INTPND_RES ; 
 int INTPND_SET ; 
 int MSGLST_RES ; 
 int MSGLST_SET ; 
 unsigned int MSGOBJ_LAST ; 
 int MSGVAL_SET ; 
 int NEWDAT_RES ; 
 int NEWDAT_SET ; 
 int RMTPND_RES ; 
 int RMTPND_UNC ; 
 int RXIE_SET ; 
 int TXIE_RES ; 
 int TXRQST_RES ; 
 int TXRQST_UNC ; 
 int cc770_read_reg (struct cc770_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc770_rx (struct net_device*,unsigned int,int) ; 
 int /*<<< orphan*/  cc770_write_reg (struct cc770_priv*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* msgobj ; 
 struct cc770_priv* netdev_priv (struct net_device*) ; 
 unsigned int obj2msgobj (unsigned int) ; 

__attribute__((used)) static void cc770_rx_interrupt(struct net_device *dev, unsigned int o)
{
	struct cc770_priv *priv = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	unsigned int mo = obj2msgobj(o);
	u8 ctrl1;
	int n = CC770_MAX_MSG;

	while (n--) {
		ctrl1 = cc770_read_reg(priv, msgobj[mo].ctrl1);

		if (!(ctrl1 & NEWDAT_SET))  {
			/* Check for RTR if additional functions are enabled */
			if (priv->control_normal_mode & CTRL_EAF) {
				if (!(cc770_read_reg(priv, msgobj[mo].ctrl0) &
				      INTPND_SET))
					break;
			} else {
				break;
			}
		}

		if (ctrl1 & MSGLST_SET) {
			stats->rx_over_errors++;
			stats->rx_errors++;
		}
		if (mo < MSGOBJ_LAST)
			cc770_write_reg(priv, msgobj[mo].ctrl1,
					NEWDAT_RES | MSGLST_RES |
					TXRQST_UNC | RMTPND_UNC);
		cc770_rx(dev, mo, ctrl1);

		cc770_write_reg(priv, msgobj[mo].ctrl0,
				MSGVAL_SET | TXIE_RES |
				RXIE_SET | INTPND_RES);
		cc770_write_reg(priv, msgobj[mo].ctrl1,
				NEWDAT_RES | MSGLST_RES |
				TXRQST_RES | RMTPND_RES);
	}
}