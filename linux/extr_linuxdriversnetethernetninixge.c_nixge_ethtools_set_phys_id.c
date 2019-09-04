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
typedef  int /*<<< orphan*/  u32 ;
struct nixge_priv {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 int /*<<< orphan*/  NIXGE_ID_LED_CTL_EN ; 
 int /*<<< orphan*/  NIXGE_ID_LED_CTL_VAL ; 
 int /*<<< orphan*/  NIXGE_REG_LED_CTL ; 
 struct nixge_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nixge_ctrl_read_reg (struct nixge_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nixge_ctrl_write_reg (struct nixge_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nixge_ethtools_set_phys_id(struct net_device *ndev,
				      enum ethtool_phys_id_state state)
{
	struct nixge_priv *priv = netdev_priv(ndev);
	u32 ctrl;

	ctrl = nixge_ctrl_read_reg(priv, NIXGE_REG_LED_CTL);
	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		ctrl |= NIXGE_ID_LED_CTL_EN;
		/* Enable identification LED override*/
		nixge_ctrl_write_reg(priv, NIXGE_REG_LED_CTL, ctrl);
		return 2;

	case ETHTOOL_ID_ON:
		ctrl |= NIXGE_ID_LED_CTL_VAL;
		nixge_ctrl_write_reg(priv, NIXGE_REG_LED_CTL, ctrl);
		break;

	case ETHTOOL_ID_OFF:
		ctrl &= ~NIXGE_ID_LED_CTL_VAL;
		nixge_ctrl_write_reg(priv, NIXGE_REG_LED_CTL, ctrl);
		break;

	case ETHTOOL_ID_INACTIVE:
		/* Restore LED settings */
		ctrl &= ~NIXGE_ID_LED_CTL_EN;
		nixge_ctrl_write_reg(priv, NIXGE_REG_LED_CTL, ctrl);
		break;
	}

	return 0;
}