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
typedef  int u8 ;
typedef  int u16 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX88179_PHY_ID ; 
 int /*<<< orphan*/  AX_ACCESS_MAC ; 
 int /*<<< orphan*/  AX_ACCESS_PHY ; 
 int /*<<< orphan*/  AX_GPIO_CTRL ; 
 int AX_GPIO_CTRL_GPIO1EN ; 
 int AX_GPIO_CTRL_GPIO2EN ; 
 int AX_GPIO_CTRL_GPIO3EN ; 
 int /*<<< orphan*/  AX_LEDCTRL ; 
 int AX_SECLD ; 
 int /*<<< orphan*/  AX_SROM_ADDR ; 
 int /*<<< orphan*/  AX_SROM_CMD ; 
 int /*<<< orphan*/  AX_SROM_DATA_HIGH ; 
 int /*<<< orphan*/  AX_SROM_DATA_LOW ; 
 int EEP_BUSY ; 
 int EEP_RD ; 
 int EINVAL ; 
 int /*<<< orphan*/  GENERAL_STATUS ; 
 int GMII_LED0_ACTIVE ; 
 int GMII_LED0_LINK_10 ; 
 int GMII_LED0_LINK_100 ; 
 int GMII_LED0_LINK_1000 ; 
 int GMII_LED1_ACTIVE ; 
 int GMII_LED1_LINK_10 ; 
 int GMII_LED1_LINK_100 ; 
 int GMII_LED1_LINK_1000 ; 
 int GMII_LED2_ACTIVE ; 
 int GMII_LED2_LINK_10 ; 
 int GMII_LED2_LINK_100 ; 
 int GMII_LED2_LINK_1000 ; 
 int GMII_LED_ACT ; 
 int GMII_LED_ACTIVE_MASK ; 
 int GMII_LED_LINK ; 
 int GMII_LED_LINK_MASK ; 
 int GMII_PHYPAGE ; 
 int GMII_PHY_PAGE_SELECT ; 
 int GMII_PHY_PGSEL_EXT ; 
 int GMII_PHY_PGSEL_PAGE0 ; 
 int HZ ; 
 int LED0_ACTIVE ; 
 int LED0_FD ; 
 int LED0_LINK_10 ; 
 int LED0_LINK_100 ; 
 int LED0_LINK_1000 ; 
 int LED0_USB3_MASK ; 
 int LED1_ACTIVE ; 
 int LED1_FD ; 
 int LED1_LINK_10 ; 
 int LED1_LINK_100 ; 
 int LED1_LINK_1000 ; 
 int LED1_USB3_MASK ; 
 int LED2_ACTIVE ; 
 int LED2_FD ; 
 int LED2_LINK_10 ; 
 int LED2_LINK_100 ; 
 int LED2_LINK_1000 ; 
 int LED2_USB3_MASK ; 
 int LED_VALID ; 
 int /*<<< orphan*/  ax88179_check_eeprom (struct usbnet*) ; 
 int /*<<< orphan*/  ax88179_check_efuse (struct usbnet*,int*) ; 
 int /*<<< orphan*/  ax88179_convert_old_led (struct usbnet*,int*) ; 
 int /*<<< orphan*/  ax88179_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 scalar_t__ ax88179_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int jiffies ; 
 scalar_t__ time_after (int,unsigned long) ; 

__attribute__((used)) static int ax88179_led_setting(struct usbnet *dev)
{
	u8 ledfd, value = 0;
	u16 tmp, ledact, ledlink, ledvalue = 0, delay = HZ / 10;
	unsigned long jtimeout;

	/* Check AX88179 version. UA1 or UA2*/
	ax88179_read_cmd(dev, AX_ACCESS_MAC, GENERAL_STATUS, 1, 1, &value);

	if (!(value & AX_SECLD)) {	/* UA1 */
		value = AX_GPIO_CTRL_GPIO3EN | AX_GPIO_CTRL_GPIO2EN |
			AX_GPIO_CTRL_GPIO1EN;
		if (ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_GPIO_CTRL,
				      1, 1, &value) < 0)
			return -EINVAL;
	}

	/* Check EEPROM */
	if (!ax88179_check_eeprom(dev)) {
		value = 0x42;
		if (ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_SROM_ADDR,
				      1, 1, &value) < 0)
			return -EINVAL;

		value = EEP_RD;
		if (ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_SROM_CMD,
				      1, 1, &value) < 0)
			return -EINVAL;

		jtimeout = jiffies + delay;
		do {
			ax88179_read_cmd(dev, AX_ACCESS_MAC, AX_SROM_CMD,
					 1, 1, &value);

			if (time_after(jiffies, jtimeout))
				return -EINVAL;

		} while (value & EEP_BUSY);

		ax88179_read_cmd(dev, AX_ACCESS_MAC, AX_SROM_DATA_HIGH,
				 1, 1, &value);
		ledvalue = (value << 8);

		ax88179_read_cmd(dev, AX_ACCESS_MAC, AX_SROM_DATA_LOW,
				 1, 1, &value);
		ledvalue |= value;

		/* load internal ROM for defaule setting */
		if ((ledvalue == 0xFFFF) || ((ledvalue & LED_VALID) == 0))
			ax88179_convert_old_led(dev, &ledvalue);

	} else if (!ax88179_check_efuse(dev, &ledvalue)) {
		if ((ledvalue == 0xFFFF) || ((ledvalue & LED_VALID) == 0))
			ax88179_convert_old_led(dev, &ledvalue);
	} else {
		ax88179_convert_old_led(dev, &ledvalue);
	}

	tmp = GMII_PHY_PGSEL_EXT;
	ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SELECT, 2, &tmp);

	tmp = 0x2c;
	ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHYPAGE, 2, &tmp);

	ax88179_read_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			 GMII_LED_ACT, 2, &ledact);

	ax88179_read_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			 GMII_LED_LINK, 2, &ledlink);

	ledact &= GMII_LED_ACTIVE_MASK;
	ledlink &= GMII_LED_LINK_MASK;

	if (ledvalue & LED0_ACTIVE)
		ledact |= GMII_LED0_ACTIVE;

	if (ledvalue & LED1_ACTIVE)
		ledact |= GMII_LED1_ACTIVE;

	if (ledvalue & LED2_ACTIVE)
		ledact |= GMII_LED2_ACTIVE;

	if (ledvalue & LED0_LINK_10)
		ledlink |= GMII_LED0_LINK_10;

	if (ledvalue & LED1_LINK_10)
		ledlink |= GMII_LED1_LINK_10;

	if (ledvalue & LED2_LINK_10)
		ledlink |= GMII_LED2_LINK_10;

	if (ledvalue & LED0_LINK_100)
		ledlink |= GMII_LED0_LINK_100;

	if (ledvalue & LED1_LINK_100)
		ledlink |= GMII_LED1_LINK_100;

	if (ledvalue & LED2_LINK_100)
		ledlink |= GMII_LED2_LINK_100;

	if (ledvalue & LED0_LINK_1000)
		ledlink |= GMII_LED0_LINK_1000;

	if (ledvalue & LED1_LINK_1000)
		ledlink |= GMII_LED1_LINK_1000;

	if (ledvalue & LED2_LINK_1000)
		ledlink |= GMII_LED2_LINK_1000;

	tmp = ledact;
	ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_LED_ACT, 2, &tmp);

	tmp = ledlink;
	ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_LED_LINK, 2, &tmp);

	tmp = GMII_PHY_PGSEL_PAGE0;
	ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SELECT, 2, &tmp);

	/* LED full duplex setting */
	ledfd = 0;
	if (ledvalue & LED0_FD)
		ledfd |= 0x01;
	else if ((ledvalue & LED0_USB3_MASK) == 0)
		ledfd |= 0x02;

	if (ledvalue & LED1_FD)
		ledfd |= 0x04;
	else if ((ledvalue & LED1_USB3_MASK) == 0)
		ledfd |= 0x08;

	if (ledvalue & LED2_FD)
		ledfd |= 0x10;
	else if ((ledvalue & LED2_USB3_MASK) == 0)
		ledfd |= 0x20;

	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_LEDCTRL, 1, 1, &ledfd);

	return 0;
}