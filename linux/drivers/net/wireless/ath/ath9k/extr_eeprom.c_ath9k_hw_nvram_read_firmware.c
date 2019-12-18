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
typedef  int /*<<< orphan*/  u16 ;
struct firmware {int size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int ath9k_hw_nvram_read_array (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath9k_hw_nvram_read_firmware(const struct firmware *eeprom_blob,
					 off_t offset, u16 *data)
{
	return ath9k_hw_nvram_read_array((u16 *) eeprom_blob->data,
					 eeprom_blob->size / sizeof(u16),
					 offset, data);
}