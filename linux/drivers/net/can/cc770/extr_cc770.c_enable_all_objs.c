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
struct net_device {int dummy; } ;
struct cc770_priv {unsigned char* obj_flags; int control_normal_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl0; int /*<<< orphan*/  ctrl1; int /*<<< orphan*/  config; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned char*) ; 
 unsigned char CC770_OBJ_FLAG_EFF ; 
 unsigned char CC770_OBJ_FLAG_RTR ; 
 unsigned char CC770_OBJ_FLAG_RX ; 
 int CPUUPD_RES ; 
 int CPUUPD_SET ; 
 int CTRL_EAF ; 
 int INTPND_RES ; 
 int MSGCFG_DIR ; 
 int MSGCFG_XTD ; 
 int MSGLST_RES ; 
 int MSGVAL_RES ; 
 int MSGVAL_SET ; 
 int NEWDAT_RES ; 
 int RMTPND_RES ; 
 int RXIE_RES ; 
 int RXIE_SET ; 
 int TXIE_RES ; 
 int TXRQST_RES ; 
 int /*<<< orphan*/  cc770_write_reg (struct cc770_priv*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* msgobj ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device const*,char*,unsigned int,...) ; 
 struct cc770_priv* netdev_priv (struct net_device const*) ; 
 unsigned int obj2msgobj (unsigned int) ; 

__attribute__((used)) static void enable_all_objs(const struct net_device *dev)
{
	struct cc770_priv *priv = netdev_priv(dev);
	u8 msgcfg;
	unsigned char obj_flags;
	unsigned int o, mo;

	for (o = 0; o < ARRAY_SIZE(priv->obj_flags); o++) {
		obj_flags = priv->obj_flags[o];
		mo = obj2msgobj(o);

		if (obj_flags & CC770_OBJ_FLAG_RX) {
			/*
			 * We don't need extra objects for RTR and EFF if
			 * the additional CC770 functions are enabled.
			 */
			if (priv->control_normal_mode & CTRL_EAF) {
				if (o > 0)
					continue;
				netdev_dbg(dev, "Message object %d for "
					   "RX data, RTR, SFF and EFF\n", mo);
			} else {
				netdev_dbg(dev,
					   "Message object %d for RX %s %s\n",
					   mo, obj_flags & CC770_OBJ_FLAG_RTR ?
					   "RTR" : "data",
					   obj_flags & CC770_OBJ_FLAG_EFF ?
					   "EFF" : "SFF");
			}

			if (obj_flags & CC770_OBJ_FLAG_EFF)
				msgcfg = MSGCFG_XTD;
			else
				msgcfg = 0;
			if (obj_flags & CC770_OBJ_FLAG_RTR)
				msgcfg |= MSGCFG_DIR;

			cc770_write_reg(priv, msgobj[mo].config, msgcfg);
			cc770_write_reg(priv, msgobj[mo].ctrl0,
					MSGVAL_SET | TXIE_RES |
					RXIE_SET | INTPND_RES);

			if (obj_flags & CC770_OBJ_FLAG_RTR)
				cc770_write_reg(priv, msgobj[mo].ctrl1,
						NEWDAT_RES | CPUUPD_SET |
						TXRQST_RES | RMTPND_RES);
			else
				cc770_write_reg(priv, msgobj[mo].ctrl1,
						NEWDAT_RES | MSGLST_RES |
						TXRQST_RES | RMTPND_RES);
		} else {
			netdev_dbg(dev, "Message object %d for "
				   "TX data, RTR, SFF and EFF\n", mo);

			cc770_write_reg(priv, msgobj[mo].ctrl1,
					RMTPND_RES | TXRQST_RES |
					CPUUPD_RES | NEWDAT_RES);
			cc770_write_reg(priv, msgobj[mo].ctrl0,
					MSGVAL_RES | TXIE_RES |
					RXIE_RES | INTPND_RES);
		}
	}
}