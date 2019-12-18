#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_1__* request; } ;
struct TYPE_2__ {int tag; } ;

/* Variables and functions */
 int HPSA_NRESERVED_CMDS ; 

__attribute__((used)) static int hpsa_get_cmd_index(struct scsi_cmnd *scmd)
{
	int idx = scmd->request->tag;

	if (idx < 0)
		return idx;

	/* Offset to leave space for internal cmds. */
	return idx += HPSA_NRESERVED_CMDS;
}