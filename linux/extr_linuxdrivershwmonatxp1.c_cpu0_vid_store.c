#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int vid; int cpu_vid; } ;
struct atxp1_data {scalar_t__ valid; TYPE_1__ reg; int /*<<< orphan*/  vrm; struct i2c_client* client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATXP1_VID ; 
 int ATXP1_VIDENA ; 
 int ATXP1_VIDMASK ; 
 struct atxp1_data* atxp1_update_device (struct device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int vid_to_reg (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t cpu0_vid_store(struct device *dev,
			      struct device_attribute *attr, const char *buf,
			      size_t count)
{
	struct atxp1_data *data = atxp1_update_device(dev);
	struct i2c_client *client = data->client;
	int vid, cvid;
	unsigned long vcore;
	int err;

	err = kstrtoul(buf, 10, &vcore);
	if (err)
		return err;

	vcore /= 25;
	vcore *= 25;

	/* Calculate VID */
	vid = vid_to_reg(vcore, data->vrm);
	if (vid < 0) {
		dev_err(dev, "VID calculation failed.\n");
		return vid;
	}

	/*
	 * If output enabled, use control register value.
	 * Otherwise original CPU VID
	 */
	if (data->reg.vid & ATXP1_VIDENA)
		cvid = data->reg.vid & ATXP1_VIDMASK;
	else
		cvid = data->reg.cpu_vid;

	/* Nothing changed, aborting */
	if (vid == cvid)
		return count;

	dev_dbg(dev, "Setting VCore to %d mV (0x%02x)\n", (int)vcore, vid);

	/* Write every 25 mV step to increase stability */
	if (cvid > vid) {
		for (; cvid >= vid; cvid--)
			i2c_smbus_write_byte_data(client,
						ATXP1_VID, cvid | ATXP1_VIDENA);
	} else {
		for (; cvid <= vid; cvid++)
			i2c_smbus_write_byte_data(client,
						ATXP1_VID, cvid | ATXP1_VIDENA);
	}

	data->valid = 0;

	return count;
}