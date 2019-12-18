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
typedef  int u32 ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  IOSS_TELEM_EVENT_WRITE ; 
 int /*<<< orphan*/  IOSS_TELEM_EVT_WRITE_SIZE ; 
 int /*<<< orphan*/  PMC_IPC_PMC_TELEMTRY ; 
 int TELEM_EVENT_ENABLE ; 
 int intel_pmc_ipc_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int telemetry_plt_config_ioss_event(u32 evt_id, int index)
{
	u32 write_buf;
	int ret;

	write_buf = evt_id | TELEM_EVENT_ENABLE;
	write_buf <<= BITS_PER_BYTE;
	write_buf |= index;

	ret = intel_pmc_ipc_command(PMC_IPC_PMC_TELEMTRY,
				    IOSS_TELEM_EVENT_WRITE, (u8 *)&write_buf,
				    IOSS_TELEM_EVT_WRITE_SIZE, NULL, 0);

	return ret;
}