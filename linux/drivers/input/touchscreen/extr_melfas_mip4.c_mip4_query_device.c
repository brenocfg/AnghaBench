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
typedef  union i2c_smbus_data {int dummy; } i2c_smbus_data ;
typedef  void* u8 ;
struct TYPE_3__ {int /*<<< orphan*/  param; int /*<<< orphan*/  app; int /*<<< orphan*/  core; int /*<<< orphan*/  boot; } ;
struct mip4_ts {void** product_name; int product_id; void** ic_name; int max_x; void** max_y; int ppm_x; void** ppm_y; int event_format; void** event_size; TYPE_2__* client; void* node_key; void* key_num; void* node_y; void* node_x; TYPE_1__ fw_version; int /*<<< orphan*/  fw_name; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  addr; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  I2C_SMBUS_BYTE ; 
 int /*<<< orphan*/  I2C_SMBUS_READ ; 
 void* MIP4_R0_EVENT ; 
 void* MIP4_R0_INFO ; 
 void* MIP4_R1_EVENT_SUPPORTED_FUNC ; 
 void* MIP4_R1_INFO_IC_NAME ; 
 void* MIP4_R1_INFO_PID ; 
 void* MIP4_R1_INFO_PRODUCT_NAME ; 
 void* MIP4_R1_INFO_RESOLUTION_X ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 void* get_unaligned_le16 (void**) ; 
 scalar_t__ i2c_smbus_xfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union i2c_smbus_data*) ; 
 int mip4_get_fw_version (struct mip4_ts*) ; 
 int mip4_i2c_xfer (struct mip4_ts*,void**,int,void**,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int mip4_query_device(struct mip4_ts *ts)
{
	union i2c_smbus_data dummy;
	int error;
	u8 cmd[2];
	u8 buf[14];

	/*
	 * Make sure there is something at this address as we do not
	 * consider subsequent failures as fatal.
	 */
	if (i2c_smbus_xfer(ts->client->adapter, ts->client->addr,
			   0, I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &dummy) < 0) {
		dev_err(&ts->client->dev, "nothing at this address\n");
		return -ENXIO;
	}

	/* Product name */
	cmd[0] = MIP4_R0_INFO;
	cmd[1] = MIP4_R1_INFO_PRODUCT_NAME;
	error = mip4_i2c_xfer(ts, cmd, sizeof(cmd),
			      ts->product_name, sizeof(ts->product_name));
	if (error)
		dev_warn(&ts->client->dev,
			 "Failed to retrieve product name: %d\n", error);
	else
		dev_dbg(&ts->client->dev, "product name: %.*s\n",
			(int)sizeof(ts->product_name), ts->product_name);

	/* Product ID */
	cmd[0] = MIP4_R0_INFO;
	cmd[1] = MIP4_R1_INFO_PID;
	error = mip4_i2c_xfer(ts, cmd, sizeof(cmd), buf, 2);
	if (error) {
		dev_warn(&ts->client->dev,
			 "Failed to retrieve product id: %d\n", error);
	} else {
		ts->product_id = get_unaligned_le16(&buf[0]);
		dev_dbg(&ts->client->dev, "product id: %04X\n", ts->product_id);
	}

	/* Firmware name */
	snprintf(ts->fw_name, sizeof(ts->fw_name),
		"melfas_mip4_%04X.fw", ts->product_id);
	dev_dbg(&ts->client->dev, "firmware name: %s\n", ts->fw_name);

	/* IC name */
	cmd[0] = MIP4_R0_INFO;
	cmd[1] = MIP4_R1_INFO_IC_NAME;
	error = mip4_i2c_xfer(ts, cmd, sizeof(cmd),
			      ts->ic_name, sizeof(ts->ic_name));
	if (error)
		dev_warn(&ts->client->dev,
			 "Failed to retrieve IC name: %d\n", error);
	else
		dev_dbg(&ts->client->dev, "IC name: %.*s\n",
			(int)sizeof(ts->ic_name), ts->ic_name);

	/* Firmware version */
	error = mip4_get_fw_version(ts);
	if (error)
		dev_warn(&ts->client->dev,
			"Failed to retrieve FW version: %d\n", error);
	else
		dev_dbg(&ts->client->dev, "F/W Version: %04X %04X %04X %04X\n",
			 ts->fw_version.boot, ts->fw_version.core,
			 ts->fw_version.app, ts->fw_version.param);

	/* Resolution */
	cmd[0] = MIP4_R0_INFO;
	cmd[1] = MIP4_R1_INFO_RESOLUTION_X;
	error = mip4_i2c_xfer(ts, cmd, sizeof(cmd), buf, 14);
	if (error) {
		dev_warn(&ts->client->dev,
			 "Failed to retrieve touchscreen parameters: %d\n",
			 error);
	} else {
		ts->max_x = get_unaligned_le16(&buf[0]);
		ts->max_y = get_unaligned_le16(&buf[2]);
		dev_dbg(&ts->client->dev, "max_x: %d, max_y: %d\n",
			ts->max_x, ts->max_y);

		ts->node_x = buf[4];
		ts->node_y = buf[5];
		ts->node_key = buf[6];
		dev_dbg(&ts->client->dev,
			"node_x: %d, node_y: %d, node_key: %d\n",
			ts->node_x, ts->node_y, ts->node_key);

		ts->ppm_x = buf[12];
		ts->ppm_y = buf[13];
		dev_dbg(&ts->client->dev, "ppm_x: %d, ppm_y: %d\n",
			ts->ppm_x, ts->ppm_y);

		/* Key ts */
		if (ts->node_key > 0)
			ts->key_num = ts->node_key;
	}

	/* Protocol */
	cmd[0] = MIP4_R0_EVENT;
	cmd[1] = MIP4_R1_EVENT_SUPPORTED_FUNC;
	error = mip4_i2c_xfer(ts, cmd, sizeof(cmd), buf, 7);
	if (error) {
		dev_warn(&ts->client->dev,
			"Failed to retrieve device type: %d\n", error);
		ts->event_format = 0xff;
	} else {
		ts->event_format = get_unaligned_le16(&buf[4]);
		ts->event_size = buf[6];
		dev_dbg(&ts->client->dev, "event_format: %d, event_size: %d\n",
			ts->event_format, ts->event_size);

		if (ts->event_format == 2 || ts->event_format > 3)
			dev_warn(&ts->client->dev,
				 "Unknown event format %d\n", ts->event_format);
	}

	return 0;
}