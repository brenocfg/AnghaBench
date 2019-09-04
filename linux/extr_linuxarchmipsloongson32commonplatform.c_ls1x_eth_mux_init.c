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
struct platform_device {int dummy; } ;
struct plat_stmmacenet_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LS1X_MUX_CTRL1 ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 

int ls1x_eth_mux_init(struct platform_device *pdev, void *priv)
{
	struct plat_stmmacenet_data *plat_dat = NULL;
	u32 val;

	val = __raw_readl(LS1X_MUX_CTRL1);

#if defined(CONFIG_LOONGSON1_LS1B)
	plat_dat = dev_get_platdata(&pdev->dev);
	if (plat_dat->bus_id) {
		__raw_writel(__raw_readl(LS1X_MUX_CTRL0) | GMAC1_USE_UART1 |
			     GMAC1_USE_UART0, LS1X_MUX_CTRL0);
		switch (plat_dat->interface) {
		case PHY_INTERFACE_MODE_RGMII:
			val &= ~(GMAC1_USE_TXCLK | GMAC1_USE_PWM23);
			break;
		case PHY_INTERFACE_MODE_MII:
			val |= (GMAC1_USE_TXCLK | GMAC1_USE_PWM23);
			break;
		default:
			pr_err("unsupported mii mode %d\n",
			       plat_dat->interface);
			return -ENOTSUPP;
		}
		val &= ~GMAC1_SHUT;
	} else {
		switch (plat_dat->interface) {
		case PHY_INTERFACE_MODE_RGMII:
			val &= ~(GMAC0_USE_TXCLK | GMAC0_USE_PWM01);
			break;
		case PHY_INTERFACE_MODE_MII:
			val |= (GMAC0_USE_TXCLK | GMAC0_USE_PWM01);
			break;
		default:
			pr_err("unsupported mii mode %d\n",
			       plat_dat->interface);
			return -ENOTSUPP;
		}
		val &= ~GMAC0_SHUT;
	}
	__raw_writel(val, LS1X_MUX_CTRL1);
#elif defined(CONFIG_LOONGSON1_LS1C)
	plat_dat = dev_get_platdata(&pdev->dev);

	val &= ~PHY_INTF_SELI;
	if (plat_dat->interface == PHY_INTERFACE_MODE_RMII)
		val |= 0x4 << PHY_INTF_SELI_SHIFT;
	__raw_writel(val, LS1X_MUX_CTRL1);

	val = __raw_readl(LS1X_MUX_CTRL0);
	__raw_writel(val & (~GMAC_SHUT), LS1X_MUX_CTRL0);
#endif

	return 0;
}