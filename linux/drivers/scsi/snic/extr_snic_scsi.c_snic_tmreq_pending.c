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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int CMD_STATE (struct scsi_cmnd*) ; 
 int SNIC_IOREQ_ABTS_PENDING ; 
 int SNIC_IOREQ_LR_PENDING ; 

__attribute__((used)) static int
snic_tmreq_pending(struct scsi_cmnd *sc)
{
	int state = CMD_STATE(sc);

	return ((state == SNIC_IOREQ_ABTS_PENDING) ||
			(state == SNIC_IOREQ_LR_PENDING));
}