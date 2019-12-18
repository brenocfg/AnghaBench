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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  high_iops_outstanding; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_busy; } ;

/* Variables and functions */
 scalar_t__ MPT3SAS_DEVICE_HIGH_IOPS_DEPTH ; 
 int MPT3SAS_HIGH_IOPS_BATCH_COUNT ; 
 int /*<<< orphan*/  MPT3SAS_HIGH_IOPS_REPLY_QUEUES ; 
 int /*<<< orphan*/  _base_get_msix_index (struct MPT3SAS_ADAPTER*,struct scsi_cmnd*) ; 
 int atomic64_add_return (int,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  base_mod64 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8
_base_get_high_iops_msix_index(struct MPT3SAS_ADAPTER *ioc,
	struct scsi_cmnd *scmd)
{
	/**
	 * Round robin the IO interrupts among the high iops
	 * reply queues in terms of batch count 16 when outstanding
	 * IOs on the target device is >=8.
	 */
	if (atomic_read(&scmd->device->device_busy) >
	    MPT3SAS_DEVICE_HIGH_IOPS_DEPTH)
		return base_mod64((
		    atomic64_add_return(1, &ioc->high_iops_outstanding) /
		    MPT3SAS_HIGH_IOPS_BATCH_COUNT),
		    MPT3SAS_HIGH_IOPS_REPLY_QUEUES);

	return _base_get_msix_index(ioc, scmd);
}