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
struct Scsi_Host {scalar_t__ shost_state; } ;

/* Variables and functions */
 scalar_t__ SHOST_RECOVERY ; 

__attribute__((used)) static int qla4xxx_is_eh_active(struct Scsi_Host *shost)
{
	if (shost->shost_state == SHOST_RECOVERY)
		return 1;
	return 0;
}