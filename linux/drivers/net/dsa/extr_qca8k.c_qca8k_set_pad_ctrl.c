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
struct qca8k_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_INTERFACE_MODE_RGMII 130 
#define  PHY_INTERFACE_MODE_RGMII_ID 129 
#define  PHY_INTERFACE_MODE_SGMII 128 
 int /*<<< orphan*/  QCA8K_MAX_DELAY ; 
 int QCA8K_PORT_PAD_RGMII_EN ; 
 int QCA8K_PORT_PAD_RGMII_RX_DELAY (int /*<<< orphan*/ ) ; 
 int QCA8K_PORT_PAD_RGMII_RX_DELAY_EN ; 
 int QCA8K_PORT_PAD_RGMII_TX_DELAY (int /*<<< orphan*/ ) ; 
 int QCA8K_PORT_PAD_SGMII_EN ; 
 int QCA8K_REG_PORT0_PAD_CTRL ; 
 int QCA8K_REG_PORT5_PAD_CTRL ; 
 int QCA8K_REG_PORT6_PAD_CTRL ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  qca8k_write (struct qca8k_priv*,int,int) ; 

__attribute__((used)) static int
qca8k_set_pad_ctrl(struct qca8k_priv *priv, int port, int mode)
{
	u32 reg, val;

	switch (port) {
	case 0:
		reg = QCA8K_REG_PORT0_PAD_CTRL;
		break;
	case 6:
		reg = QCA8K_REG_PORT6_PAD_CTRL;
		break;
	default:
		pr_err("Can't set PAD_CTRL on port %d\n", port);
		return -EINVAL;
	}

	/* Configure a port to be directly connected to an external
	 * PHY or MAC.
	 */
	switch (mode) {
	case PHY_INTERFACE_MODE_RGMII:
		/* RGMII mode means no delay so don't enable the delay */
		val = QCA8K_PORT_PAD_RGMII_EN;
		qca8k_write(priv, reg, val);
		break;
	case PHY_INTERFACE_MODE_RGMII_ID:
		/* RGMII_ID needs internal delay. This is enabled through
		 * PORT5_PAD_CTRL for all ports, rather than individual port
		 * registers
		 */
		qca8k_write(priv, reg,
			    QCA8K_PORT_PAD_RGMII_EN |
			    QCA8K_PORT_PAD_RGMII_TX_DELAY(QCA8K_MAX_DELAY) |
			    QCA8K_PORT_PAD_RGMII_RX_DELAY(QCA8K_MAX_DELAY));
		qca8k_write(priv, QCA8K_REG_PORT5_PAD_CTRL,
			    QCA8K_PORT_PAD_RGMII_RX_DELAY_EN);
		break;
	case PHY_INTERFACE_MODE_SGMII:
		qca8k_write(priv, reg, QCA8K_PORT_PAD_SGMII_EN);
		break;
	default:
		pr_err("xMII mode %d not supported\n", mode);
		return -EINVAL;
	}

	return 0;
}