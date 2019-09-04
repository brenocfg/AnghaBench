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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {struct device* parent; } ;
struct i2c_adapter {TYPE_1__ dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  EETag ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MICNG_EETAG_END0 ; 
 scalar_t__ MICNG_EETAG_END1 ; 
 scalar_t__ MICNG_EE_END ; 
 scalar_t__ MICNG_EE_START ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int i2c_read_eeprom (struct i2c_adapter*,int,scalar_t__,int*,int) ; 
 int i2c_write_eeprom (struct i2c_adapter*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int WriteEEProm(struct i2c_adapter *adapter,
		       u16 Tag, u32 Length, u8 *data)
{
	struct device *pdev = adapter->dev.parent;
	int status = 0;
	u16 Addr = MICNG_EE_START;
	u8 EETag[3];
	u16 tag = 0;
	int retry, i;

	while (Addr + sizeof(u16) + 1 < MICNG_EE_END) {
		if (i2c_read_eeprom(adapter, 0x50, Addr, EETag, sizeof(EETag)))
			return -1;
		tag = (EETag[0] << 8) | EETag[1];
		if (tag == MICNG_EETAG_END0 || tag == MICNG_EETAG_END1)
			return -1;
		if (tag == Tag)
			break;
		Addr += sizeof(u16) + 1 + EETag[2];
	}
	if (Addr + sizeof(u16) + 1 + EETag[2] > MICNG_EE_END) {
		dev_err(pdev, "Reached EOEE @ Tag = %04x Length = %3d\n",
			tag, EETag[2]);
		return -1;
	}

	if (Length > EETag[2])
		return -EINVAL;
	/* Note: We write the data one byte at a time to avoid
	   issues with page sizes. (which are different for
	   each manufacture and eeprom size)
	 */
	Addr += sizeof(u16) + 1;
	for (i = 0; i < Length; i++, Addr++) {
		status = i2c_write_eeprom(adapter, 0x50, Addr, data[i]);

		if (status)
			break;

		/* Poll for finishing write cycle */
		retry = 10;
		while (retry) {
			u8 Tmp;

			msleep(50);
			status = i2c_read_eeprom(adapter, 0x50, Addr, &Tmp, 1);
			if (status)
				break;
			if (Tmp != data[i])
				dev_err(pdev, "eeprom write error\n");
			retry -= 1;
		}
		if (status) {
			dev_err(pdev, "Timeout polling eeprom\n");
			break;
		}
	}
	return status;
}