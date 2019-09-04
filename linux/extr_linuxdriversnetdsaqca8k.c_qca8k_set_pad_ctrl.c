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
struct qca8k_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_INTERFACE_MODE_RGMII 129 
#define  PHY_INTERFACE_MODE_SGMII 128 
 int QCA8K_PORT_PAD_RGMII_EN ; 
 int QCA8K_PORT_PAD_RGMII_RX_DELAY (int) ; 
 int QCA8K_PORT_PAD_RGMII_RX_DELAY_EN ; 
 int QCA8K_PORT_PAD_RGMII_TX_DELAY (int) ; 
 int QCA8K_PORT_PAD_SGMII_EN ; 
 int /*<<< orphan*/  QCA8K_REG_PORT0_PAD_CTRL ; 
 int /*<<< orphan*/  QCA8K_REG_PORT5_PAD_CTRL ; 
 int /*<<< orphan*/  QCA8K_REG_PORT6_PAD_CTRL ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  qca8k_write (struct qca8k_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
qca8k_set_pad_ctrl(struct qca8k_priv *priv, int port, int mode)
{
	u32 reg;

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
		qca8k_write(priv, reg,
			    QCA8K_PORT_PAD_RGMII_EN |
			    QCA8K_PORT_PAD_RGMII_TX_DELAY(3) |
			    QCA8K_PORT_PAD_RGMII_RX_DELAY(3));

		/* According to the datasheet, RGMII delay is enabled through
		 * PORT5_PAD_CTRL for all ports, rather than individual port
		 * registers
		 */
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