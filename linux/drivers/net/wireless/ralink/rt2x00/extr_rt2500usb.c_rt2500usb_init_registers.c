#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct rt2x00_dev {TYPE_3__* rx; TYPE_2__* ops; } ;
struct TYPE_6__ {int data_size; } ;
struct TYPE_5__ {TYPE_1__* lib; } ;
struct TYPE_4__ {scalar_t__ (* set_device_state ) (struct rt2x00_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CIPHER_NONE ; 
 int EBUSY ; 
 int IEEE80211_HEADER ; 
 int /*<<< orphan*/  MAC_CSR1 ; 
 int /*<<< orphan*/  MAC_CSR11 ; 
 int /*<<< orphan*/  MAC_CSR13 ; 
 int /*<<< orphan*/  MAC_CSR14 ; 
 int /*<<< orphan*/  MAC_CSR15 ; 
 int /*<<< orphan*/  MAC_CSR16 ; 
 int /*<<< orphan*/  MAC_CSR18 ; 
 int /*<<< orphan*/  MAC_CSR18_DELAY_AFTER_BEACON ; 
 int /*<<< orphan*/  MAC_CSR1_BBP_RESET ; 
 int /*<<< orphan*/  MAC_CSR1_HOST_READY ; 
 int /*<<< orphan*/  MAC_CSR1_SOFT_RESET ; 
 int /*<<< orphan*/  MAC_CSR22 ; 
 int /*<<< orphan*/  MAC_CSR8 ; 
 int /*<<< orphan*/  MAC_CSR8_MAX_FRAME_UNIT ; 
 int /*<<< orphan*/  MAC_CSR9 ; 
 int /*<<< orphan*/  PHY_CSR2 ; 
 int /*<<< orphan*/  PHY_CSR2_LNA ; 
 int /*<<< orphan*/  PHY_CSR2_LNA_MODE ; 
 int /*<<< orphan*/  PHY_CSR4 ; 
 int /*<<< orphan*/  PHY_CSR4_LOW_RF_LE ; 
 int /*<<< orphan*/  REGISTER_TIMEOUT ; 
 scalar_t__ RT2570_VERSION_C ; 
 int /*<<< orphan*/  STATE_AWAKE ; 
 int /*<<< orphan*/  TXRX_CSR0 ; 
 int /*<<< orphan*/  TXRX_CSR0_ALGORITHM ; 
 int /*<<< orphan*/  TXRX_CSR0_IV_OFFSET ; 
 int /*<<< orphan*/  TXRX_CSR0_KEY_ID ; 
 int /*<<< orphan*/  TXRX_CSR1 ; 
 int /*<<< orphan*/  TXRX_CSR19 ; 
 int /*<<< orphan*/  TXRX_CSR19_BEACON_GEN ; 
 int /*<<< orphan*/  TXRX_CSR19_TBCN ; 
 int /*<<< orphan*/  TXRX_CSR19_TSF_COUNT ; 
 int /*<<< orphan*/  TXRX_CSR19_TSF_SYNC ; 
 int /*<<< orphan*/  TXRX_CSR1_AUTO_SEQUENCE ; 
 int /*<<< orphan*/  TXRX_CSR2 ; 
 int /*<<< orphan*/  TXRX_CSR21 ; 
 int /*<<< orphan*/  TXRX_CSR2_DISABLE_RX ; 
 int /*<<< orphan*/  TXRX_CSR5 ; 
 int /*<<< orphan*/  TXRX_CSR5_BBP_ID0 ; 
 int /*<<< orphan*/  TXRX_CSR5_BBP_ID0_VALID ; 
 int /*<<< orphan*/  TXRX_CSR5_BBP_ID1 ; 
 int /*<<< orphan*/  TXRX_CSR5_BBP_ID1_VALID ; 
 int /*<<< orphan*/  TXRX_CSR6 ; 
 int /*<<< orphan*/  TXRX_CSR6_BBP_ID0 ; 
 int /*<<< orphan*/  TXRX_CSR6_BBP_ID0_VALID ; 
 int /*<<< orphan*/  TXRX_CSR6_BBP_ID1 ; 
 int /*<<< orphan*/  TXRX_CSR6_BBP_ID1_VALID ; 
 int /*<<< orphan*/  TXRX_CSR7 ; 
 int /*<<< orphan*/  TXRX_CSR7_BBP_ID0 ; 
 int /*<<< orphan*/  TXRX_CSR7_BBP_ID0_VALID ; 
 int /*<<< orphan*/  TXRX_CSR7_BBP_ID1 ; 
 int /*<<< orphan*/  TXRX_CSR7_BBP_ID1_VALID ; 
 int /*<<< orphan*/  TXRX_CSR8 ; 
 int /*<<< orphan*/  TXRX_CSR8_BBP_ID0 ; 
 int /*<<< orphan*/  TXRX_CSR8_BBP_ID0_VALID ; 
 int /*<<< orphan*/  TXRX_CSR8_BBP_ID1 ; 
 int /*<<< orphan*/  TXRX_CSR8_BBP_ID1_VALID ; 
 int /*<<< orphan*/  USB_DEVICE_MODE ; 
 int USB_MODE_TEST ; 
 int /*<<< orphan*/  USB_SINGLE_WRITE ; 
 int rt2500usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2500usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rt2x00_rev (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00usb_vendor_request_sw (struct rt2x00_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2500usb_init_registers(struct rt2x00_dev *rt2x00dev)
{
	u16 reg;

	rt2x00usb_vendor_request_sw(rt2x00dev, USB_DEVICE_MODE, 0x0001,
				    USB_MODE_TEST, REGISTER_TIMEOUT);
	rt2x00usb_vendor_request_sw(rt2x00dev, USB_SINGLE_WRITE, 0x0308,
				    0x00f0, REGISTER_TIMEOUT);

	reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR2);
	rt2x00_set_field16(&reg, TXRX_CSR2_DISABLE_RX, 1);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR2, reg);

	rt2500usb_register_write(rt2x00dev, MAC_CSR13, 0x1111);
	rt2500usb_register_write(rt2x00dev, MAC_CSR14, 0x1e11);

	reg = rt2500usb_register_read(rt2x00dev, MAC_CSR1);
	rt2x00_set_field16(&reg, MAC_CSR1_SOFT_RESET, 1);
	rt2x00_set_field16(&reg, MAC_CSR1_BBP_RESET, 1);
	rt2x00_set_field16(&reg, MAC_CSR1_HOST_READY, 0);
	rt2500usb_register_write(rt2x00dev, MAC_CSR1, reg);

	reg = rt2500usb_register_read(rt2x00dev, MAC_CSR1);
	rt2x00_set_field16(&reg, MAC_CSR1_SOFT_RESET, 0);
	rt2x00_set_field16(&reg, MAC_CSR1_BBP_RESET, 0);
	rt2x00_set_field16(&reg, MAC_CSR1_HOST_READY, 0);
	rt2500usb_register_write(rt2x00dev, MAC_CSR1, reg);

	reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR5);
	rt2x00_set_field16(&reg, TXRX_CSR5_BBP_ID0, 13);
	rt2x00_set_field16(&reg, TXRX_CSR5_BBP_ID0_VALID, 1);
	rt2x00_set_field16(&reg, TXRX_CSR5_BBP_ID1, 12);
	rt2x00_set_field16(&reg, TXRX_CSR5_BBP_ID1_VALID, 1);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR5, reg);

	reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR6);
	rt2x00_set_field16(&reg, TXRX_CSR6_BBP_ID0, 10);
	rt2x00_set_field16(&reg, TXRX_CSR6_BBP_ID0_VALID, 1);
	rt2x00_set_field16(&reg, TXRX_CSR6_BBP_ID1, 11);
	rt2x00_set_field16(&reg, TXRX_CSR6_BBP_ID1_VALID, 1);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR6, reg);

	reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR7);
	rt2x00_set_field16(&reg, TXRX_CSR7_BBP_ID0, 7);
	rt2x00_set_field16(&reg, TXRX_CSR7_BBP_ID0_VALID, 1);
	rt2x00_set_field16(&reg, TXRX_CSR7_BBP_ID1, 6);
	rt2x00_set_field16(&reg, TXRX_CSR7_BBP_ID1_VALID, 1);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR7, reg);

	reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR8);
	rt2x00_set_field16(&reg, TXRX_CSR8_BBP_ID0, 5);
	rt2x00_set_field16(&reg, TXRX_CSR8_BBP_ID0_VALID, 1);
	rt2x00_set_field16(&reg, TXRX_CSR8_BBP_ID1, 0);
	rt2x00_set_field16(&reg, TXRX_CSR8_BBP_ID1_VALID, 0);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR8, reg);

	reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR19);
	rt2x00_set_field16(&reg, TXRX_CSR19_TSF_COUNT, 0);
	rt2x00_set_field16(&reg, TXRX_CSR19_TSF_SYNC, 0);
	rt2x00_set_field16(&reg, TXRX_CSR19_TBCN, 0);
	rt2x00_set_field16(&reg, TXRX_CSR19_BEACON_GEN, 0);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR19, reg);

	rt2500usb_register_write(rt2x00dev, TXRX_CSR21, 0xe78f);
	rt2500usb_register_write(rt2x00dev, MAC_CSR9, 0xff1d);

	if (rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_AWAKE))
		return -EBUSY;

	reg = rt2500usb_register_read(rt2x00dev, MAC_CSR1);
	rt2x00_set_field16(&reg, MAC_CSR1_SOFT_RESET, 0);
	rt2x00_set_field16(&reg, MAC_CSR1_BBP_RESET, 0);
	rt2x00_set_field16(&reg, MAC_CSR1_HOST_READY, 1);
	rt2500usb_register_write(rt2x00dev, MAC_CSR1, reg);

	if (rt2x00_rev(rt2x00dev) >= RT2570_VERSION_C) {
		reg = rt2500usb_register_read(rt2x00dev, PHY_CSR2);
		rt2x00_set_field16(&reg, PHY_CSR2_LNA, 0);
	} else {
		reg = 0;
		rt2x00_set_field16(&reg, PHY_CSR2_LNA, 1);
		rt2x00_set_field16(&reg, PHY_CSR2_LNA_MODE, 3);
	}
	rt2500usb_register_write(rt2x00dev, PHY_CSR2, reg);

	rt2500usb_register_write(rt2x00dev, MAC_CSR11, 0x0002);
	rt2500usb_register_write(rt2x00dev, MAC_CSR22, 0x0053);
	rt2500usb_register_write(rt2x00dev, MAC_CSR15, 0x01ee);
	rt2500usb_register_write(rt2x00dev, MAC_CSR16, 0x0000);

	reg = rt2500usb_register_read(rt2x00dev, MAC_CSR8);
	rt2x00_set_field16(&reg, MAC_CSR8_MAX_FRAME_UNIT,
			   rt2x00dev->rx->data_size);
	rt2500usb_register_write(rt2x00dev, MAC_CSR8, reg);

	reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR0);
	rt2x00_set_field16(&reg, TXRX_CSR0_ALGORITHM, CIPHER_NONE);
	rt2x00_set_field16(&reg, TXRX_CSR0_IV_OFFSET, IEEE80211_HEADER);
	rt2x00_set_field16(&reg, TXRX_CSR0_KEY_ID, 0);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR0, reg);

	reg = rt2500usb_register_read(rt2x00dev, MAC_CSR18);
	rt2x00_set_field16(&reg, MAC_CSR18_DELAY_AFTER_BEACON, 90);
	rt2500usb_register_write(rt2x00dev, MAC_CSR18, reg);

	reg = rt2500usb_register_read(rt2x00dev, PHY_CSR4);
	rt2x00_set_field16(&reg, PHY_CSR4_LOW_RF_LE, 1);
	rt2500usb_register_write(rt2x00dev, PHY_CSR4, reg);

	reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR1);
	rt2x00_set_field16(&reg, TXRX_CSR1_AUTO_SEQUENCE, 1);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR1, reg);

	return 0;
}