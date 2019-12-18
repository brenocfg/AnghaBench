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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {struct device* parent; } ;
struct i2c_adapter {TYPE_1__ dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  EETag ;

/* Variables and functions */
 scalar_t__ MICNG_EETAG_END0 ; 
 scalar_t__ MICNG_EETAG_END1 ; 
 scalar_t__ MICNG_EE_END ; 
 scalar_t__ MICNG_EE_START ; 
 int STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,int) ; 
 int i2c_read_eeprom (struct i2c_adapter*,int,scalar_t__,int*,scalar_t__) ; 

__attribute__((used)) static int ReadEEProm(struct i2c_adapter *adapter,
		      u16 Tag, u32 MaxLen, u8 *data, u32 *pLength)
{
	struct device *pdev = adapter->dev.parent;
	int status = 0;
	u16 Addr = MICNG_EE_START, Length, tag = 0;
	u8  EETag[3];

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
	Length = EETag[2];
	if (Length > MaxLen)
		Length = (u16) MaxLen;
	if (Length > 0) {
		Addr += sizeof(u16) + 1;
		status = i2c_read_eeprom(adapter, 0x50, Addr, data, Length);
		if (!status) {
			*pLength = EETag[2];
#if 0
			if (Length < EETag[2])
				status = STATUS_BUFFER_OVERFLOW;
#endif
		}
	}
	return status;
}