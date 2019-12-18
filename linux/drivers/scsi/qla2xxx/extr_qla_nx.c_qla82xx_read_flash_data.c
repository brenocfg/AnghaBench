#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct qla_hw_data {int dummy; } ;
struct TYPE_4__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 scalar_t__ qla82xx_rom_fast_read (struct qla_hw_data*,int,int*) ; 

__attribute__((used)) static uint32_t *
qla82xx_read_flash_data(scsi_qla_host_t *vha, uint32_t *dwptr, uint32_t faddr,
	uint32_t length)
{
	uint32_t i;
	uint32_t val;
	struct qla_hw_data *ha = vha->hw;

	/* Dword reads to flash. */
	for (i = 0; i < length/4; i++, faddr += 4) {
		if (qla82xx_rom_fast_read(ha, faddr, &val)) {
			ql_log(ql_log_warn, vha, 0x0106,
			    "Do ROM fast read failed.\n");
			goto done_read;
		}
		dwptr[i] = cpu_to_le32(val);
	}
done_read:
	return dwptr;
}