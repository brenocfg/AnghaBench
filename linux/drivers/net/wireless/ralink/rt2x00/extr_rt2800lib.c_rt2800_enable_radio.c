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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_LED_ACT_CONF ; 
 int /*<<< orphan*/  EEPROM_LED_AG_CONF ; 
 int /*<<< orphan*/  EEPROM_LED_POLARITY ; 
 int EIO ; 
 int /*<<< orphan*/  H2M_BBP_AGENT ; 
 int /*<<< orphan*/  H2M_INT_SRC ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR ; 
 int /*<<< orphan*/  MAC_SYS_CTRL ; 
 int /*<<< orphan*/  MAC_SYS_CTRL_ENABLE_RX ; 
 int /*<<< orphan*/  MAC_SYS_CTRL_ENABLE_TX ; 
 int /*<<< orphan*/  MCU_BOOT_SIGNAL ; 
 int /*<<< orphan*/  MCU_CURRENT ; 
 int /*<<< orphan*/  MCU_LED_ACT_CONF ; 
 int /*<<< orphan*/  MCU_LED_AG_CONF ; 
 int /*<<< orphan*/  MCU_LED_LED_POLARITY ; 
 int /*<<< orphan*/  RT3070 ; 
 int /*<<< orphan*/  RT3071 ; 
 int /*<<< orphan*/  RT3572 ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_ENABLE_RX_DMA ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_ENABLE_TX_DMA ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_TX_WRITEBACK_DONE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rt2800_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_init_bbp (struct rt2x00_dev*) ; 
 scalar_t__ rt2800_init_registers (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_rfcsr (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_mcu_request (struct rt2x00_dev*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int rt2800_wait_bbp_ready (struct rt2x00_dev*) ; 
 int rt2800_wait_bbp_rf_ready (struct rt2x00_dev*) ; 
 scalar_t__ rt2800_wait_wpdma_ready (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_is_usb (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

int rt2800_enable_radio(struct rt2x00_dev *rt2x00dev)
{
	u32 reg;
	u16 word;

	/*
	 * Initialize MAC registers.
	 */
	if (unlikely(rt2800_wait_wpdma_ready(rt2x00dev) ||
		     rt2800_init_registers(rt2x00dev)))
		return -EIO;

	/*
	 * Wait BBP/RF to wake up.
	 */
	if (unlikely(rt2800_wait_bbp_rf_ready(rt2x00dev)))
		return -EIO;

	/*
	 * Send signal during boot time to initialize firmware.
	 */
	rt2800_register_write(rt2x00dev, H2M_BBP_AGENT, 0);
	rt2800_register_write(rt2x00dev, H2M_MAILBOX_CSR, 0);
	if (rt2x00_is_usb(rt2x00dev))
		rt2800_register_write(rt2x00dev, H2M_INT_SRC, 0);
	rt2800_mcu_request(rt2x00dev, MCU_BOOT_SIGNAL, 0, 0, 0);
	msleep(1);

	/*
	 * Make sure BBP is up and running.
	 */
	if (unlikely(rt2800_wait_bbp_ready(rt2x00dev)))
		return -EIO;

	/*
	 * Initialize BBP/RF registers.
	 */
	rt2800_init_bbp(rt2x00dev);
	rt2800_init_rfcsr(rt2x00dev);

	if (rt2x00_is_usb(rt2x00dev) &&
	    (rt2x00_rt(rt2x00dev, RT3070) ||
	     rt2x00_rt(rt2x00dev, RT3071) ||
	     rt2x00_rt(rt2x00dev, RT3572))) {
		udelay(200);
		rt2800_mcu_request(rt2x00dev, MCU_CURRENT, 0, 0, 0);
		udelay(10);
	}

	/*
	 * Enable RX.
	 */
	reg = rt2800_register_read(rt2x00dev, MAC_SYS_CTRL);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_TX, 1);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 0);
	rt2800_register_write(rt2x00dev, MAC_SYS_CTRL, reg);

	udelay(50);

	reg = rt2800_register_read(rt2x00dev, WPDMA_GLO_CFG);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_ENABLE_TX_DMA, 1);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_ENABLE_RX_DMA, 1);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_TX_WRITEBACK_DONE, 1);
	rt2800_register_write(rt2x00dev, WPDMA_GLO_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, MAC_SYS_CTRL);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_TX, 1);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 1);
	rt2800_register_write(rt2x00dev, MAC_SYS_CTRL, reg);

	/*
	 * Initialize LED control
	 */
	word = rt2800_eeprom_read(rt2x00dev, EEPROM_LED_AG_CONF);
	rt2800_mcu_request(rt2x00dev, MCU_LED_AG_CONF, 0xff,
			   word & 0xff, (word >> 8) & 0xff);

	word = rt2800_eeprom_read(rt2x00dev, EEPROM_LED_ACT_CONF);
	rt2800_mcu_request(rt2x00dev, MCU_LED_ACT_CONF, 0xff,
			   word & 0xff, (word >> 8) & 0xff);

	word = rt2800_eeprom_read(rt2x00dev, EEPROM_LED_POLARITY);
	rt2800_mcu_request(rt2x00dev, MCU_LED_LED_POLARITY, 0xff,
			   word & 0xff, (word >> 8) & 0xff);

	return 0;
}