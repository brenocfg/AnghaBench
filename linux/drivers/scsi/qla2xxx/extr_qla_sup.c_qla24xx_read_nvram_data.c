#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void uint8_t ;
typedef  int uint32_t ;
struct qla_hw_data {int dummy; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ IS_P3P_TYPE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  cpu_to_le32s (int*) ; 
 int nvram_data_addr (struct qla_hw_data*,int) ; 
 scalar_t__ qla24xx_read_flash_dword (struct qla_hw_data*,int,int*) ; 

uint8_t *
qla24xx_read_nvram_data(scsi_qla_host_t *vha, void *buf, uint32_t naddr,
    uint32_t bytes)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t *dwptr = buf;
	uint32_t i;

	if (IS_P3P_TYPE(ha))
		return  buf;

	/* Dword reads to flash. */
	naddr = nvram_data_addr(ha, naddr);
	bytes >>= 2;
	for (i = 0; i < bytes; i++, naddr++, dwptr++) {
		if (qla24xx_read_flash_dword(ha, naddr, dwptr))
			break;
		cpu_to_le32s(dwptr);
	}

	return buf;
}