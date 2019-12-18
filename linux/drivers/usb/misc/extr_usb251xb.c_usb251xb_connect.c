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
struct usb251xb {int vendor_id; int product_id; int device_id; char conf_data1; char conf_data2; char conf_data3; char non_rem_dev; char port_disable_sp; char port_disable_bp; char max_power_sp; char max_power_bp; char max_current_sp; char max_current_bp; char power_on_time; int lang_id; char manufacturer_len; char product_len; char serial_len; char* manufacturer; char* serial; char* product; char bat_charge_en; char boost_up; char boost_57; char boost_14; char port_swap; char port_map12; char port_map34; char port_map56; char port_map7; int /*<<< orphan*/  i2c; scalar_t__ skip_config; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t USB251XB_ADDR_BATTERY_CHARGING_ENABLE ; 
 size_t USB251XB_ADDR_BOOST_14 ; 
 size_t USB251XB_ADDR_BOOST_57 ; 
 size_t USB251XB_ADDR_BOOST_UP ; 
 size_t USB251XB_ADDR_CONFIG_DATA_1 ; 
 size_t USB251XB_ADDR_CONFIG_DATA_2 ; 
 size_t USB251XB_ADDR_CONFIG_DATA_3 ; 
 size_t USB251XB_ADDR_DEVICE_ID_LSB ; 
 size_t USB251XB_ADDR_DEVICE_ID_MSB ; 
 size_t USB251XB_ADDR_LANGUAGE_ID_HIGH ; 
 size_t USB251XB_ADDR_LANGUAGE_ID_LOW ; 
 size_t USB251XB_ADDR_MANUFACTURER_STRING ; 
 size_t USB251XB_ADDR_MANUFACTURER_STRING_LEN ; 
 size_t USB251XB_ADDR_MAX_CURRENT_BUS ; 
 size_t USB251XB_ADDR_MAX_CURRENT_SELF ; 
 size_t USB251XB_ADDR_MAX_POWER_BUS ; 
 size_t USB251XB_ADDR_MAX_POWER_SELF ; 
 size_t USB251XB_ADDR_NON_REMOVABLE_DEVICES ; 
 size_t USB251XB_ADDR_PORT_DISABLE_BUS ; 
 size_t USB251XB_ADDR_PORT_DISABLE_SELF ; 
 size_t USB251XB_ADDR_PORT_MAP_12 ; 
 size_t USB251XB_ADDR_PORT_MAP_34 ; 
 size_t USB251XB_ADDR_PORT_MAP_56 ; 
 size_t USB251XB_ADDR_PORT_MAP_7 ; 
 size_t USB251XB_ADDR_PORT_SWAP ; 
 size_t USB251XB_ADDR_POWER_ON_TIME ; 
 size_t USB251XB_ADDR_PRODUCT_ID_LSB ; 
 size_t USB251XB_ADDR_PRODUCT_ID_MSB ; 
 size_t USB251XB_ADDR_PRODUCT_STRING ; 
 size_t USB251XB_ADDR_PRODUCT_STRING_LEN ; 
 size_t USB251XB_ADDR_SERIAL_STRING ; 
 size_t USB251XB_ADDR_SERIAL_STRING_LEN ; 
 size_t USB251XB_ADDR_STATUS_COMMAND ; 
 size_t USB251XB_ADDR_VENDOR_ID_LSB ; 
 size_t USB251XB_ADDR_VENDOR_ID_MSB ; 
 int USB251XB_I2C_REG_SZ ; 
 int USB251XB_I2C_WRITE_SZ ; 
 char USB251XB_STATUS_COMMAND_ATTACH ; 
 int USB251XB_STRING_BUFSIZE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int i2c_smbus_write_i2c_block_data (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb251xb_reset (struct usb251xb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb251xb_connect(struct usb251xb *hub)
{
	struct device *dev = hub->dev;
	int err, i;
	char i2c_wb[USB251XB_I2C_REG_SZ];

	memset(i2c_wb, 0, USB251XB_I2C_REG_SZ);

	if (hub->skip_config) {
		dev_info(dev, "Skip hub configuration, only attach.\n");
		i2c_wb[0] = 0x01;
		i2c_wb[1] = USB251XB_STATUS_COMMAND_ATTACH;

		usb251xb_reset(hub, 0);

		err = i2c_smbus_write_i2c_block_data(hub->i2c,
				USB251XB_ADDR_STATUS_COMMAND, 2, i2c_wb);
		if (err) {
			dev_err(dev, "attaching hub failed: %d\n", err);
			return err;
		}
		return 0;
	}

	i2c_wb[USB251XB_ADDR_VENDOR_ID_MSB]     = (hub->vendor_id >> 8) & 0xFF;
	i2c_wb[USB251XB_ADDR_VENDOR_ID_LSB]     = hub->vendor_id & 0xFF;
	i2c_wb[USB251XB_ADDR_PRODUCT_ID_MSB]    = (hub->product_id >> 8) & 0xFF;
	i2c_wb[USB251XB_ADDR_PRODUCT_ID_LSB]    = hub->product_id & 0xFF;
	i2c_wb[USB251XB_ADDR_DEVICE_ID_MSB]     = (hub->device_id >> 8) & 0xFF;
	i2c_wb[USB251XB_ADDR_DEVICE_ID_LSB]     = hub->device_id & 0xFF;
	i2c_wb[USB251XB_ADDR_CONFIG_DATA_1]     = hub->conf_data1;
	i2c_wb[USB251XB_ADDR_CONFIG_DATA_2]     = hub->conf_data2;
	i2c_wb[USB251XB_ADDR_CONFIG_DATA_3]     = hub->conf_data3;
	i2c_wb[USB251XB_ADDR_NON_REMOVABLE_DEVICES] = hub->non_rem_dev;
	i2c_wb[USB251XB_ADDR_PORT_DISABLE_SELF] = hub->port_disable_sp;
	i2c_wb[USB251XB_ADDR_PORT_DISABLE_BUS]  = hub->port_disable_bp;
	i2c_wb[USB251XB_ADDR_MAX_POWER_SELF]    = hub->max_power_sp;
	i2c_wb[USB251XB_ADDR_MAX_POWER_BUS]     = hub->max_power_bp;
	i2c_wb[USB251XB_ADDR_MAX_CURRENT_SELF]  = hub->max_current_sp;
	i2c_wb[USB251XB_ADDR_MAX_CURRENT_BUS]   = hub->max_current_bp;
	i2c_wb[USB251XB_ADDR_POWER_ON_TIME]     = hub->power_on_time;
	i2c_wb[USB251XB_ADDR_LANGUAGE_ID_HIGH]  = (hub->lang_id >> 8) & 0xFF;
	i2c_wb[USB251XB_ADDR_LANGUAGE_ID_LOW]   = hub->lang_id & 0xFF;
	i2c_wb[USB251XB_ADDR_MANUFACTURER_STRING_LEN] = hub->manufacturer_len;
	i2c_wb[USB251XB_ADDR_PRODUCT_STRING_LEN]      = hub->product_len;
	i2c_wb[USB251XB_ADDR_SERIAL_STRING_LEN]       = hub->serial_len;
	memcpy(&i2c_wb[USB251XB_ADDR_MANUFACTURER_STRING], hub->manufacturer,
	       USB251XB_STRING_BUFSIZE);
	memcpy(&i2c_wb[USB251XB_ADDR_SERIAL_STRING], hub->serial,
	       USB251XB_STRING_BUFSIZE);
	memcpy(&i2c_wb[USB251XB_ADDR_PRODUCT_STRING], hub->product,
	       USB251XB_STRING_BUFSIZE);
	i2c_wb[USB251XB_ADDR_BATTERY_CHARGING_ENABLE] = hub->bat_charge_en;
	i2c_wb[USB251XB_ADDR_BOOST_UP]          = hub->boost_up;
	i2c_wb[USB251XB_ADDR_BOOST_57]          = hub->boost_57;
	i2c_wb[USB251XB_ADDR_BOOST_14]          = hub->boost_14;
	i2c_wb[USB251XB_ADDR_PORT_SWAP]         = hub->port_swap;
	i2c_wb[USB251XB_ADDR_PORT_MAP_12]       = hub->port_map12;
	i2c_wb[USB251XB_ADDR_PORT_MAP_34]       = hub->port_map34;
	i2c_wb[USB251XB_ADDR_PORT_MAP_56]       = hub->port_map56;
	i2c_wb[USB251XB_ADDR_PORT_MAP_7]        = hub->port_map7;
	i2c_wb[USB251XB_ADDR_STATUS_COMMAND] = USB251XB_STATUS_COMMAND_ATTACH;

	usb251xb_reset(hub, 0);

	/* write registers */
	for (i = 0; i < (USB251XB_I2C_REG_SZ / USB251XB_I2C_WRITE_SZ); i++) {
		int offset = i * USB251XB_I2C_WRITE_SZ;
		char wbuf[USB251XB_I2C_WRITE_SZ + 1];

		/* The first data byte transferred tells the hub how many data
		 * bytes will follow (byte count).
		 */
		wbuf[0] = USB251XB_I2C_WRITE_SZ;
		memcpy(&wbuf[1], &i2c_wb[offset], USB251XB_I2C_WRITE_SZ);

		dev_dbg(dev, "writing %d byte block %d to 0x%02X\n",
			USB251XB_I2C_WRITE_SZ, i, offset);

		err = i2c_smbus_write_i2c_block_data(hub->i2c, offset,
						     USB251XB_I2C_WRITE_SZ + 1,
						     wbuf);
		if (err)
			goto out_err;
	}

	dev_info(dev, "Hub configuration was successful.\n");
	return 0;

out_err:
	dev_err(dev, "configuring block %d failed: %d\n", i, err);
	return err;
}