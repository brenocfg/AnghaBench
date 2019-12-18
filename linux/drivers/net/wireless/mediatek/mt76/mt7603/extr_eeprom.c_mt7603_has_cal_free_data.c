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
typedef  int /*<<< orphan*/  u8 ;
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 size_t MT_EE_CP_FT_VERSION ; 
 size_t MT_EE_TEMP_SENSOR_CAL ; 
 int MT_EE_TX_POWER_0_START_2G ; 
 int MT_EE_TX_POWER_1_START_2G ; 
 size_t MT_EE_XTAL_FREQ_OFFSET ; 
 size_t MT_EE_XTAL_WF_RFCAL ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
mt7603_has_cal_free_data(struct mt7603_dev *dev, u8 *efuse)
{
	if (!efuse[MT_EE_TEMP_SENSOR_CAL])
		return false;

	if (get_unaligned_le16(efuse + MT_EE_TX_POWER_0_START_2G) == 0)
		return false;

	if (get_unaligned_le16(efuse + MT_EE_TX_POWER_1_START_2G) == 0)
		return false;

	if (!efuse[MT_EE_CP_FT_VERSION])
		return false;

	if (!efuse[MT_EE_XTAL_FREQ_OFFSET])
		return false;

	if (!efuse[MT_EE_XTAL_WF_RFCAL])
		return false;

	return true;
}