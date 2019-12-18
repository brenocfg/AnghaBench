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
struct mac_delay_struct {int tx_delay; int tx_inv; int rx_delay; int rx_inv; } ;
struct mediatek_dwmac_plat_data {int phy_mode; int /*<<< orphan*/  peri_regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  rmii_rxc; struct mac_delay_struct mac_delay; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_DLY_GTXC_ENABLE ; 
 int /*<<< orphan*/  ETH_DLY_GTXC_INV ; 
 int /*<<< orphan*/  ETH_DLY_GTXC_STAGES ; 
 int /*<<< orphan*/  ETH_DLY_RXC_ENABLE ; 
 int /*<<< orphan*/  ETH_DLY_RXC_INV ; 
 int /*<<< orphan*/  ETH_DLY_RXC_STAGES ; 
 int /*<<< orphan*/  ETH_DLY_TXC_ENABLE ; 
 int /*<<< orphan*/  ETH_DLY_TXC_INV ; 
 int /*<<< orphan*/  ETH_DLY_TXC_STAGES ; 
 int ETH_FINE_DLY_GTXC ; 
 int ETH_FINE_DLY_RXC ; 
 int ETH_RMII_DLY_TX_INV ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PERI_ETH_DLY ; 
 int /*<<< orphan*/  PERI_ETH_DLY_FINE ; 
#define  PHY_INTERFACE_MODE_MII 133 
#define  PHY_INTERFACE_MODE_RGMII 132 
#define  PHY_INTERFACE_MODE_RGMII_ID 131 
#define  PHY_INTERFACE_MODE_RGMII_RXID 130 
#define  PHY_INTERFACE_MODE_RGMII_TXID 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mt2712_delay_ps2stage (struct mediatek_dwmac_plat_data*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt2712_set_delay(struct mediatek_dwmac_plat_data *plat)
{
	struct mac_delay_struct *mac_delay = &plat->mac_delay;
	u32 delay_val = 0, fine_val = 0;

	mt2712_delay_ps2stage(plat);

	switch (plat->phy_mode) {
	case PHY_INTERFACE_MODE_MII:
		delay_val |= FIELD_PREP(ETH_DLY_TXC_ENABLE, !!mac_delay->tx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_TXC_STAGES, mac_delay->tx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_TXC_INV, mac_delay->tx_inv);

		delay_val |= FIELD_PREP(ETH_DLY_RXC_ENABLE, !!mac_delay->rx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_RXC_STAGES, mac_delay->rx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_RXC_INV, mac_delay->rx_inv);
		break;
	case PHY_INTERFACE_MODE_RMII:
		/* the rmii reference clock is from external phy,
		 * and the property "rmii_rxc" indicates which pin(TXC/RXC)
		 * the reference clk is connected to. The reference clock is a
		 * received signal, so rx_delay/rx_inv are used to indicate
		 * the reference clock timing adjustment
		 */
		if (plat->rmii_rxc) {
			/* the rmii reference clock from outside is connected
			 * to RXC pin, the reference clock will be adjusted
			 * by RXC delay macro circuit.
			 */
			delay_val |= FIELD_PREP(ETH_DLY_RXC_ENABLE, !!mac_delay->rx_delay);
			delay_val |= FIELD_PREP(ETH_DLY_RXC_STAGES, mac_delay->rx_delay);
			delay_val |= FIELD_PREP(ETH_DLY_RXC_INV, mac_delay->rx_inv);
		} else {
			/* the rmii reference clock from outside is connected
			 * to TXC pin, the reference clock will be adjusted
			 * by TXC delay macro circuit.
			 */
			delay_val |= FIELD_PREP(ETH_DLY_TXC_ENABLE, !!mac_delay->rx_delay);
			delay_val |= FIELD_PREP(ETH_DLY_TXC_STAGES, mac_delay->rx_delay);
			delay_val |= FIELD_PREP(ETH_DLY_TXC_INV, mac_delay->rx_inv);
		}
		/* tx_inv will inverse the tx clock inside mac relateive to
		 * reference clock from external phy,
		 * and this bit is located in the same register with fine-tune
		 */
		if (mac_delay->tx_inv)
			fine_val = ETH_RMII_DLY_TX_INV;
		break;
	case PHY_INTERFACE_MODE_RGMII:
	case PHY_INTERFACE_MODE_RGMII_TXID:
	case PHY_INTERFACE_MODE_RGMII_RXID:
	case PHY_INTERFACE_MODE_RGMII_ID:
		fine_val = ETH_FINE_DLY_GTXC | ETH_FINE_DLY_RXC;

		delay_val |= FIELD_PREP(ETH_DLY_GTXC_ENABLE, !!mac_delay->tx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_GTXC_STAGES, mac_delay->tx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_GTXC_INV, mac_delay->tx_inv);

		delay_val |= FIELD_PREP(ETH_DLY_RXC_ENABLE, !!mac_delay->rx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_RXC_STAGES, mac_delay->rx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_RXC_INV, mac_delay->rx_inv);
		break;
	default:
		dev_err(plat->dev, "phy interface not supported\n");
		return -EINVAL;
	}
	regmap_write(plat->peri_regmap, PERI_ETH_DLY, delay_val);
	regmap_write(plat->peri_regmap, PERI_ETH_DLY_FINE, fine_val);

	return 0;
}