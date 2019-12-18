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
typedef  int /*<<< orphan*/  u16 ;
struct scsi_device {int /*<<< orphan*/  sdev_gendev; } ;
struct esas2r_adapter {TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESAS2R_LOG_INFO ; 
 int /*<<< orphan*/  ESAS2R_LOG_WARN ; 
 int /*<<< orphan*/  SDEV_OFFLINE ; 
 int /*<<< orphan*/  esas2r_log_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 struct scsi_device* scsi_device_lookup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_device_put (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_device_set_state (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_device (struct scsi_device*) ; 

__attribute__((used)) static void esas2r_remove_device(struct esas2r_adapter *a, u16 target_id)
{
	struct scsi_device *scsi_dev;

	scsi_dev = scsi_device_lookup(a->host, 0, target_id, 0);

	if (scsi_dev) {
		scsi_device_set_state(scsi_dev, SDEV_OFFLINE);

		esas2r_log_dev(
			ESAS2R_LOG_INFO,
			&(scsi_dev->
			  sdev_gendev),
			"scsi_remove_device() called for 0:%d:0",
			target_id);

		scsi_remove_device(scsi_dev);

		esas2r_log_dev(
			ESAS2R_LOG_INFO,
			&(scsi_dev->
			  sdev_gendev),
			"scsi_device_put() called");

		scsi_device_put(scsi_dev);
	} else {
		esas2r_log_dev(
			ESAS2R_LOG_WARN,
			&(a->host->shost_gendev),
			"no target found at id %d",
			target_id);
	}
}