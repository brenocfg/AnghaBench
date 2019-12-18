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
typedef  int u32 ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct adm8211_priv* priv; } ;
struct adm8211_priv {scalar_t__ bbp_type; int specific_bbptype; int transceiver_type; TYPE_2__* eeprom; TYPE_1__* pdev; } ;
struct TYPE_4__ {int major_version; int cr28; int cr29; } ;
struct TYPE_3__ {int revision; } ;

/* Variables and functions */
#define  ADM8211_AL2210L 139 
 int ADM8211_BBPCTL_TYPE ; 
#define  ADM8211_BBP_ADM8011 138 
#define  ADM8211_BBP_RFMD3000 137 
#define  ADM8211_BBP_RFMD3002 136 
 int ADM8211_CSR_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM8211_CSR_WRITE (int /*<<< orphan*/ ,int) ; 
#define  ADM8211_MAX2820 135 
#define  ADM8211_REV_AB 134 
#define  ADM8211_REV_AF 133 
#define  ADM8211_REV_BA 132 
#define  ADM8211_REV_CA 131 
#define  ADM8211_RFMD2948 130 
#define  ADM8211_RFMD2958 129 
#define  ADM8211_RFMD2958_RF3000_CONTROL_POWER 128 
 int ADM8211_SYNCTL_SELCAL ; 
 int ADM8211_SYNRF_PE1 ; 
 int ADM8211_SYNRF_PHYRST ; 
 int ADM8211_SYNRF_SELRF ; 
 scalar_t__ ADM8211_TYPE_ADMTEK ; 
 scalar_t__ ADM8211_TYPE_INTERSIL ; 
 scalar_t__ ADM8211_TYPE_RFMD ; 
 int /*<<< orphan*/  BBPCTL ; 
 int /*<<< orphan*/  MACTEST ; 
 int /*<<< orphan*/  MMIRD0 ; 
 int /*<<< orphan*/  MMIRD1 ; 
 int /*<<< orphan*/  MMIWA ; 
 int RF3000_CCA_CTRL ; 
 int RF3000_DIVERSITY__RSSI ; 
 int RF3000_HIGH_GAIN_CALIB ; 
 int RF3000_LOW_GAIN_CALIB ; 
 int RF3000_TX_VAR_GAIN__TX_LEN_EXT ; 
 int /*<<< orphan*/  SYNCTL ; 
 int /*<<< orphan*/  SYNRF ; 
 int /*<<< orphan*/  adm8211_hw_init_syn (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  adm8211_write_bbp (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int adm8211_hw_init_bbp(struct ieee80211_hw *dev)
{
	struct adm8211_priv *priv = dev->priv;
	u32 reg;

	/* write addresses */
	if (priv->bbp_type == ADM8211_TYPE_INTERSIL) {
		ADM8211_CSR_WRITE(MMIWA,  0x100E0C0A);
		ADM8211_CSR_WRITE(MMIRD0, 0x00007C7E);
		ADM8211_CSR_WRITE(MMIRD1, 0x00100000);
	} else if (priv->bbp_type == ADM8211_TYPE_RFMD ||
		   priv->bbp_type == ADM8211_TYPE_ADMTEK) {
		/* check specific BBP type */
		switch (priv->specific_bbptype) {
		case ADM8211_BBP_RFMD3000:
		case ADM8211_BBP_RFMD3002:
			ADM8211_CSR_WRITE(MMIWA,  0x00009101);
			ADM8211_CSR_WRITE(MMIRD0, 0x00000301);
			break;

		case ADM8211_BBP_ADM8011:
			ADM8211_CSR_WRITE(MMIWA,  0x00008903);
			ADM8211_CSR_WRITE(MMIRD0, 0x00001716);

			reg = ADM8211_CSR_READ(BBPCTL);
			reg &= ~ADM8211_BBPCTL_TYPE;
			reg |= 0x5 << 18;
			ADM8211_CSR_WRITE(BBPCTL, reg);
			break;
		}

		switch (priv->pdev->revision) {
		case ADM8211_REV_CA:
			if (priv->transceiver_type == ADM8211_RFMD2958 ||
			    priv->transceiver_type == ADM8211_RFMD2958_RF3000_CONTROL_POWER ||
			    priv->transceiver_type == ADM8211_RFMD2948)
				ADM8211_CSR_WRITE(SYNCTL, 0x1 << 22);
			else if (priv->transceiver_type == ADM8211_MAX2820 ||
				 priv->transceiver_type == ADM8211_AL2210L)
				ADM8211_CSR_WRITE(SYNCTL, 0x3 << 22);
			break;

		case ADM8211_REV_BA:
			reg  = ADM8211_CSR_READ(MMIRD1);
			reg &= 0x0000FFFF;
			reg |= 0x7e100000;
			ADM8211_CSR_WRITE(MMIRD1, reg);
			break;

		case ADM8211_REV_AB:
		case ADM8211_REV_AF:
		default:
			ADM8211_CSR_WRITE(MMIRD1, 0x7e100000);
			break;
		}

		/* For RFMD */
		ADM8211_CSR_WRITE(MACTEST, 0x800);
	}

	adm8211_hw_init_syn(dev);

	/* Set RF Power control IF pin to PE1+PHYRST# */
	ADM8211_CSR_WRITE(SYNRF, ADM8211_SYNRF_SELRF |
			  ADM8211_SYNRF_PE1 | ADM8211_SYNRF_PHYRST);
	ADM8211_CSR_READ(SYNRF);
	msleep(20);

	/* write BBP regs */
	if (priv->bbp_type == ADM8211_TYPE_RFMD) {
		/* RF3000 BBP */
		/* another set:
		 * 11: c8
		 * 14: 14
		 * 15: 50 (chan 1..13; chan 14: d0)
		 * 1c: 00
		 * 1d: 84
		 */
		adm8211_write_bbp(dev, RF3000_CCA_CTRL, 0x80);
		/* antenna selection: diversity */
		adm8211_write_bbp(dev, RF3000_DIVERSITY__RSSI, 0x80);
		adm8211_write_bbp(dev, RF3000_TX_VAR_GAIN__TX_LEN_EXT, 0x74);
		adm8211_write_bbp(dev, RF3000_LOW_GAIN_CALIB, 0x38);
		adm8211_write_bbp(dev, RF3000_HIGH_GAIN_CALIB, 0x40);

		if (priv->eeprom->major_version < 2) {
			adm8211_write_bbp(dev, 0x1c, 0x00);
			adm8211_write_bbp(dev, 0x1d, 0x80);
		} else {
			if (priv->pdev->revision == ADM8211_REV_BA)
				adm8211_write_bbp(dev, 0x1c, priv->eeprom->cr28);
			else
				adm8211_write_bbp(dev, 0x1c, 0x00);

			adm8211_write_bbp(dev, 0x1d, priv->eeprom->cr29);
		}
	} else if (priv->bbp_type == ADM8211_TYPE_ADMTEK) {
		/* reset baseband */
		adm8211_write_bbp(dev, 0x00, 0xFF);
		/* antenna selection: diversity */
		adm8211_write_bbp(dev, 0x07, 0x0A);

		/* TODO: find documentation for this */
		switch (priv->transceiver_type) {
		case ADM8211_RFMD2958:
		case ADM8211_RFMD2958_RF3000_CONTROL_POWER:
			adm8211_write_bbp(dev, 0x00, 0x00);
			adm8211_write_bbp(dev, 0x01, 0x00);
			adm8211_write_bbp(dev, 0x02, 0x00);
			adm8211_write_bbp(dev, 0x03, 0x00);
			adm8211_write_bbp(dev, 0x06, 0x0f);
			adm8211_write_bbp(dev, 0x09, 0x00);
			adm8211_write_bbp(dev, 0x0a, 0x00);
			adm8211_write_bbp(dev, 0x0b, 0x00);
			adm8211_write_bbp(dev, 0x0c, 0x00);
			adm8211_write_bbp(dev, 0x0f, 0xAA);
			adm8211_write_bbp(dev, 0x10, 0x8c);
			adm8211_write_bbp(dev, 0x11, 0x43);
			adm8211_write_bbp(dev, 0x18, 0x40);
			adm8211_write_bbp(dev, 0x20, 0x23);
			adm8211_write_bbp(dev, 0x21, 0x02);
			adm8211_write_bbp(dev, 0x22, 0x28);
			adm8211_write_bbp(dev, 0x23, 0x30);
			adm8211_write_bbp(dev, 0x24, 0x2d);
			adm8211_write_bbp(dev, 0x28, 0x35);
			adm8211_write_bbp(dev, 0x2a, 0x8c);
			adm8211_write_bbp(dev, 0x2b, 0x81);
			adm8211_write_bbp(dev, 0x2c, 0x44);
			adm8211_write_bbp(dev, 0x2d, 0x0A);
			adm8211_write_bbp(dev, 0x29, 0x40);
			adm8211_write_bbp(dev, 0x60, 0x08);
			adm8211_write_bbp(dev, 0x64, 0x01);
			break;

		case ADM8211_MAX2820:
			adm8211_write_bbp(dev, 0x00, 0x00);
			adm8211_write_bbp(dev, 0x01, 0x00);
			adm8211_write_bbp(dev, 0x02, 0x00);
			adm8211_write_bbp(dev, 0x03, 0x00);
			adm8211_write_bbp(dev, 0x06, 0x0f);
			adm8211_write_bbp(dev, 0x09, 0x05);
			adm8211_write_bbp(dev, 0x0a, 0x02);
			adm8211_write_bbp(dev, 0x0b, 0x00);
			adm8211_write_bbp(dev, 0x0c, 0x0f);
			adm8211_write_bbp(dev, 0x0f, 0x55);
			adm8211_write_bbp(dev, 0x10, 0x8d);
			adm8211_write_bbp(dev, 0x11, 0x43);
			adm8211_write_bbp(dev, 0x18, 0x4a);
			adm8211_write_bbp(dev, 0x20, 0x20);
			adm8211_write_bbp(dev, 0x21, 0x02);
			adm8211_write_bbp(dev, 0x22, 0x23);
			adm8211_write_bbp(dev, 0x23, 0x30);
			adm8211_write_bbp(dev, 0x24, 0x2d);
			adm8211_write_bbp(dev, 0x2a, 0x8c);
			adm8211_write_bbp(dev, 0x2b, 0x81);
			adm8211_write_bbp(dev, 0x2c, 0x44);
			adm8211_write_bbp(dev, 0x29, 0x4a);
			adm8211_write_bbp(dev, 0x60, 0x2b);
			adm8211_write_bbp(dev, 0x64, 0x01);
			break;

		case ADM8211_AL2210L:
			adm8211_write_bbp(dev, 0x00, 0x00);
			adm8211_write_bbp(dev, 0x01, 0x00);
			adm8211_write_bbp(dev, 0x02, 0x00);
			adm8211_write_bbp(dev, 0x03, 0x00);
			adm8211_write_bbp(dev, 0x06, 0x0f);
			adm8211_write_bbp(dev, 0x07, 0x05);
			adm8211_write_bbp(dev, 0x08, 0x03);
			adm8211_write_bbp(dev, 0x09, 0x00);
			adm8211_write_bbp(dev, 0x0a, 0x00);
			adm8211_write_bbp(dev, 0x0b, 0x00);
			adm8211_write_bbp(dev, 0x0c, 0x10);
			adm8211_write_bbp(dev, 0x0f, 0x55);
			adm8211_write_bbp(dev, 0x10, 0x8d);
			adm8211_write_bbp(dev, 0x11, 0x43);
			adm8211_write_bbp(dev, 0x18, 0x4a);
			adm8211_write_bbp(dev, 0x20, 0x20);
			adm8211_write_bbp(dev, 0x21, 0x02);
			adm8211_write_bbp(dev, 0x22, 0x23);
			adm8211_write_bbp(dev, 0x23, 0x30);
			adm8211_write_bbp(dev, 0x24, 0x2d);
			adm8211_write_bbp(dev, 0x2a, 0xaa);
			adm8211_write_bbp(dev, 0x2b, 0x81);
			adm8211_write_bbp(dev, 0x2c, 0x44);
			adm8211_write_bbp(dev, 0x29, 0xfa);
			adm8211_write_bbp(dev, 0x60, 0x2d);
			adm8211_write_bbp(dev, 0x64, 0x01);
			break;

		case ADM8211_RFMD2948:
			break;

		default:
			wiphy_debug(dev->wiphy, "unsupported transceiver %d\n",
				    priv->transceiver_type);
			break;
		}
	} else
		wiphy_debug(dev->wiphy, "unsupported BBP %d\n", priv->bbp_type);

	ADM8211_CSR_WRITE(SYNRF, 0);

	/* Set RF CAL control source to MAC control */
	reg = ADM8211_CSR_READ(SYNCTL);
	reg |= ADM8211_SYNCTL_SELCAL;
	ADM8211_CSR_WRITE(SYNCTL, reg);

	return 0;
}