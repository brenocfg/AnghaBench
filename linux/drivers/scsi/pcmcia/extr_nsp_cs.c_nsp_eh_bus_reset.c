#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  nsp_hw_data ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSP_DEBUG_BUSRESET ; 
 int nsp_bus_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*,struct scsi_cmnd*) ; 

__attribute__((used)) static int nsp_eh_bus_reset(struct scsi_cmnd *SCpnt)
{
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	nsp_dbg(NSP_DEBUG_BUSRESET, "SCpnt=0x%p", SCpnt);

	return nsp_bus_reset(data);
}