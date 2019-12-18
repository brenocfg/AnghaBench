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
typedef  int u8 ;
struct TYPE_3__ {int* data; } ;
struct TYPE_4__ {TYPE_1__ eeprom; } ;
struct mt7603_dev {TYPE_2__ mt76; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
#define  MT_EE_CP_FT_VERSION 133 
#define  MT_EE_TEMP_SENSOR_CAL 132 
#define  MT_EE_TX_POWER_0_START_2G 131 
#define  MT_EE_TX_POWER_1_START_2G 130 
#define  MT_EE_XTAL_FREQ_OFFSET 129 
#define  MT_EE_XTAL_WF_RFCAL 128 
 scalar_t__ is_mt7628 (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_has_cal_free_data (struct mt7603_dev*,int*) ; 

__attribute__((used)) static void
mt7603_apply_cal_free_data(struct mt7603_dev *dev, u8 *efuse)
{
	static const u8 cal_free_bytes[] = {
		MT_EE_TEMP_SENSOR_CAL,
		MT_EE_CP_FT_VERSION,
		MT_EE_XTAL_FREQ_OFFSET,
		MT_EE_XTAL_WF_RFCAL,
		/* Skip for MT7628 */
		MT_EE_TX_POWER_0_START_2G,
		MT_EE_TX_POWER_0_START_2G + 1,
		MT_EE_TX_POWER_1_START_2G,
		MT_EE_TX_POWER_1_START_2G + 1,
	};
	u8 *eeprom = dev->mt76.eeprom.data;
	int n = ARRAY_SIZE(cal_free_bytes);
	int i;

	if (!mt7603_has_cal_free_data(dev, efuse))
		return;

	if (is_mt7628(dev))
		n -= 4;

	for (i = 0; i < n; i++) {
		int offset = cal_free_bytes[i];

		eeprom[offset] = efuse[offset];
	}
}