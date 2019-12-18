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
struct mt7601u_dev {int /*<<< orphan*/  dev; TYPE_1__* ee; } ;
typedef  int s8 ;
struct TYPE_2__ {int* rssi_offset; } ;

/* Variables and functions */
 int MT_EE_RSSI_OFFSET ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
mt7601u_set_rssi_offset(struct mt7601u_dev *dev, u8 *eeprom)
{
	int i;
	s8 *rssi_offset = dev->ee->rssi_offset;

	for (i = 0; i < 2; i++) {
		rssi_offset[i] = eeprom[MT_EE_RSSI_OFFSET + i];

		if (rssi_offset[i] < -10 || rssi_offset[i] > 10) {
			dev_warn(dev->dev,
				 "Warning: EEPROM RSSI is invalid %02hhx\n",
				 rssi_offset[i]);
			rssi_offset[i] = 0;
		}
	}
}