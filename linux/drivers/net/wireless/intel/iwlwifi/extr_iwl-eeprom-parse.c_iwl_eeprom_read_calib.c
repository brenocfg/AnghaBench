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
struct iwl_nvm_data {int /*<<< orphan*/  calib_voltage; int /*<<< orphan*/  calib_version; } ;
struct iwl_eeprom_calib_hdr {int /*<<< orphan*/  voltage; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_CALIB_ALL ; 
 int ENODATA ; 
 scalar_t__ iwl_eeprom_query_addr (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_eeprom_read_calib(const u8 *eeprom, size_t eeprom_size,
				 struct iwl_nvm_data *data)
{
	struct iwl_eeprom_calib_hdr *hdr;

	hdr = (void *)iwl_eeprom_query_addr(eeprom, eeprom_size,
					    EEPROM_CALIB_ALL);
	if (!hdr)
		return -ENODATA;
	data->calib_version = hdr->version;
	data->calib_voltage = hdr->voltage;

	return 0;
}