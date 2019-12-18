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
typedef  scalar_t__ ulong ;
typedef  scalar_t__ uint32_t ;
struct qla_hw_data {int dummy; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  cpu_to_le32s (scalar_t__*) ; 
 scalar_t__ flash_data_addr (struct qla_hw_data*,scalar_t__) ; 
 int qla24xx_read_flash_dword (struct qla_hw_data*,scalar_t__,scalar_t__*) ; 

int
qla24xx_read_flash_data(scsi_qla_host_t *vha, uint32_t *dwptr, uint32_t faddr,
    uint32_t dwords)
{
	ulong i;
	int ret = QLA_SUCCESS;
	struct qla_hw_data *ha = vha->hw;

	/* Dword reads to flash. */
	faddr =  flash_data_addr(ha, faddr);
	for (i = 0; i < dwords; i++, faddr++, dwptr++) {
		ret = qla24xx_read_flash_dword(ha, faddr, dwptr);
		if (ret != QLA_SUCCESS)
			break;
		cpu_to_le32s(dwptr);
	}

	return ret;
}