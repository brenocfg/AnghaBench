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
struct net_device {int dummy; } ;
struct c_can_priv {int (* read_reg ) (struct c_can_priv*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CONTROL_INIT ; 
 int /*<<< orphan*/  C_CAN_CTRL_REG ; 
 int EIO ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int stub1 (struct c_can_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int c_can_wait_for_ctrl_init(struct net_device *dev,
				    struct c_can_priv *priv, u32 init)
{
	int retry = 0;

	while (init != (priv->read_reg(priv, C_CAN_CTRL_REG) & CONTROL_INIT)) {
		udelay(10);
		if (retry++ > 1000) {
			netdev_err(dev, "CCTRL: set CONTROL_INIT failed\n");
			return -EIO;
		}
	}
	return 0;
}