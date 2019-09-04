#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lun; TYPE_1__* vtarget; int /*<<< orphan*/  configured_lun; } ;
typedef  TYPE_2__ VirtDevice ;
struct TYPE_8__ {int physDiskNum; int data_dma; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; scalar_t__ rsvd2; scalar_t__ rsvd; scalar_t__ size; int /*<<< orphan*/ * data; scalar_t__ flags; int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {int tflags; scalar_t__ type; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; scalar_t__ deleted; } ;
typedef  int /*<<< orphan*/  MPT_SCSI_HOST ;
typedef  TYPE_3__ INTERNAL_CMD ;

/* Variables and functions */
 int MPT_TARGET_FLAGS_RAID_COMPONENT ; 
 int /*<<< orphan*/  SYNCHRONIZE_CACHE ; 
 scalar_t__ TYPE_DISK ; 
 int /*<<< orphan*/  mptscsih_do_cmd (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void
mptscsih_synchronize_cache(MPT_SCSI_HOST *hd, VirtDevice *vdevice)
{
	INTERNAL_CMD		 iocmd;

	/* Ignore hidden raid components, this is handled when the command
	 * is sent to the volume
	 */
	if (vdevice->vtarget->tflags & MPT_TARGET_FLAGS_RAID_COMPONENT)
		return;

	if (vdevice->vtarget->type != TYPE_DISK || vdevice->vtarget->deleted ||
	    !vdevice->configured_lun)
		return;

	/* Following parameters will not change
	 * in this routine.
	 */
	iocmd.cmd = SYNCHRONIZE_CACHE;
	iocmd.flags = 0;
	iocmd.physDiskNum = -1;
	iocmd.data = NULL;
	iocmd.data_dma = -1;
	iocmd.size = 0;
	iocmd.rsvd = iocmd.rsvd2 = 0;
	iocmd.channel = vdevice->vtarget->channel;
	iocmd.id = vdevice->vtarget->id;
	iocmd.lun = vdevice->lun;

	mptscsih_do_cmd(hd, &iocmd);
}