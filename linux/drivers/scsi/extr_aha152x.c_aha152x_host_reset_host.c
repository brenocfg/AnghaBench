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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  aha152x_bus_reset_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  reset_ports (struct Scsi_Host*) ; 

int aha152x_host_reset_host(struct Scsi_Host *shpnt)
{
	aha152x_bus_reset_host(shpnt);
	reset_ports(shpnt);

	return SUCCESS;
}