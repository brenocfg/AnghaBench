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
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeprom_readword (int,int /*<<< orphan*/ *,struct scsi_qla_host*) ; 

u16 rd_nvram_word(struct scsi_qla_host * ha, int offset)
{
	u16 val = 0;

	/* NOTE: NVRAM uses half-word addresses */
	eeprom_readword(offset, &val, ha);
	return val;
}