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
struct eeprom_table_record {unsigned char err_type; unsigned char bank; int ts; int offset; unsigned char mem_channel; unsigned char mcumc_id; int retired_page; } ;
struct amdgpu_ras_eeprom_control {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void __decode_table_record_from_buff(struct amdgpu_ras_eeprom_control *control,
					    struct eeprom_table_record *record,
					    unsigned char *buff)
{
	__le64 tmp = 0;
	int i =  0;

	/* Next are all record fields according to EEPROM page spec in LE foramt */
	record->err_type = buff[i++];

	record->bank = buff[i++];

	memcpy(&tmp, buff + i, 8);
	record->ts = le64_to_cpu(tmp);
	i += 8;

	memcpy(&tmp, buff + i, 6);
	record->offset = (le64_to_cpu(tmp) & 0xffffffffffff);
	i += 6;

	buff[i++] = record->mem_channel;
	buff[i++] = record->mcumc_id;

	memcpy(&tmp, buff + i,  6);
	record->retired_page = (le64_to_cpu(tmp) & 0xffffffffffff);
}