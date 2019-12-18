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
struct ath9k_platform_data {int /*<<< orphan*/  eeprom_data; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ath9k_hw_nvram_read_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath9k_hw_nvram_read_pdata(struct ath9k_platform_data *pdata,
				      off_t offset, u16 *data)
{
	return ath9k_hw_nvram_read_array(pdata->eeprom_data,
					 ARRAY_SIZE(pdata->eeprom_data),
					 offset, data);
}