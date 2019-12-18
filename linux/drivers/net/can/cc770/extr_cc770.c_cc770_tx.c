#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct cc770_priv {TYPE_1__* tx_skb; } ;
struct can_frame {int can_dlc; int can_id; int* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl0; int /*<<< orphan*/  ctrl1; int /*<<< orphan*/ * data; int /*<<< orphan*/ * id; int /*<<< orphan*/  config; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 int CPUUPD_RES ; 
 int CPUUPD_SET ; 
 int INTPND_RES ; 
 int INTPND_UNC ; 
 int MSGCFG_DIR ; 
 int MSGCFG_XTD ; 
 int MSGVAL_RES ; 
 int MSGVAL_SET ; 
 int NEWDAT_RES ; 
 int NEWDAT_UNC ; 
 int RMTPND_RES ; 
 int RMTPND_UNC ; 
 int RXIE_RES ; 
 int RXIE_SET ; 
 int TXIE_RES ; 
 int TXIE_SET ; 
 int TXRQST_RES ; 
 int TXRQST_SET ; 
 int /*<<< orphan*/  cc770_write_reg (struct cc770_priv*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* msgobj ; 
 struct cc770_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void cc770_tx(struct net_device *dev, int mo)
{
	struct cc770_priv *priv = netdev_priv(dev);
	struct can_frame *cf = (struct can_frame *)priv->tx_skb->data;
	u8 dlc, rtr;
	u32 id;
	int i;

	dlc = cf->can_dlc;
	id = cf->can_id;
	rtr = cf->can_id & CAN_RTR_FLAG ? 0 : MSGCFG_DIR;

	cc770_write_reg(priv, msgobj[mo].ctrl0,
			MSGVAL_RES | TXIE_RES | RXIE_RES | INTPND_RES);
	cc770_write_reg(priv, msgobj[mo].ctrl1,
			RMTPND_RES | TXRQST_RES | CPUUPD_SET | NEWDAT_RES);

	if (id & CAN_EFF_FLAG) {
		id &= CAN_EFF_MASK;
		cc770_write_reg(priv, msgobj[mo].config,
				(dlc << 4) | rtr | MSGCFG_XTD);
		cc770_write_reg(priv, msgobj[mo].id[3], id << 3);
		cc770_write_reg(priv, msgobj[mo].id[2], id >> 5);
		cc770_write_reg(priv, msgobj[mo].id[1], id >> 13);
		cc770_write_reg(priv, msgobj[mo].id[0], id >> 21);
	} else {
		id &= CAN_SFF_MASK;
		cc770_write_reg(priv, msgobj[mo].config, (dlc << 4) | rtr);
		cc770_write_reg(priv, msgobj[mo].id[0], id >> 3);
		cc770_write_reg(priv, msgobj[mo].id[1], id << 5);
	}

	for (i = 0; i < dlc; i++)
		cc770_write_reg(priv, msgobj[mo].data[i], cf->data[i]);

	cc770_write_reg(priv, msgobj[mo].ctrl1,
			RMTPND_UNC | TXRQST_SET | CPUUPD_RES | NEWDAT_UNC);
	cc770_write_reg(priv, msgobj[mo].ctrl0,
			MSGVAL_SET | TXIE_SET | RXIE_SET | INTPND_UNC);
}