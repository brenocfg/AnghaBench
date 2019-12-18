#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct se_cmd {TYPE_1__* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_5__ {unsigned char page; } ;
struct TYPE_4__ {int dev_flags; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int DF_EMULATED_VPD_UNIT_SERIAL ; 
 TYPE_2__* evpd_handlers ; 

__attribute__((used)) static sense_reason_t
spc_emulate_evpd_00(struct se_cmd *cmd, unsigned char *buf)
{
	int p;

	/*
	 * Only report the INQUIRY EVPD=1 pages after a valid NAA
	 * Registered Extended LUN WWN has been set via ConfigFS
	 * during device creation/restart.
	 */
	if (cmd->se_dev->dev_flags & DF_EMULATED_VPD_UNIT_SERIAL) {
		buf[3] = ARRAY_SIZE(evpd_handlers);
		for (p = 0; p < ARRAY_SIZE(evpd_handlers); ++p)
			buf[p + 4] = evpd_handlers[p].page;
	}

	return 0;
}