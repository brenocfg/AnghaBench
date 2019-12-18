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
typedef  int /*<<< orphan*/  u32 ;
struct rt_fw_blob {int size; scalar_t__ data; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ MAX_FW_SIZE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,char const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ round_up (int,int) ; 
 int /*<<< orphan*/  swab32p (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool _rtl92e_fw_prepare(struct net_device *dev, struct rt_fw_blob *blob,
			       const char *name, u8 padding)
{
	const struct firmware *fw;
	int rc, i;
	bool ret = true;

	rc = request_firmware(&fw, name, &dev->dev);
	if (rc < 0)
		return false;

	if (round_up(fw->size, 4) > MAX_FW_SIZE - padding) {
		netdev_err(dev, "Firmware image %s too big for the device.\n",
			   name);
		ret = false;
		goto out;
	}

	if (padding)
		memset(blob->data, 0, padding);
	if (fw->size % 4)
		memset(blob->data + padding + fw->size, 0, 4);
	memcpy(blob->data + padding, fw->data, fw->size);

	blob->size = round_up(fw->size, 4) + padding;

	/* Swap endian - firmware is packaged in invalid endiannes*/
	for (i = padding; i < blob->size; i += 4) {
		u32 *data = (u32 *)(blob->data + i);
		*data = swab32p(data);
	}
out:
	release_firmware(fw);
	return ret;
}