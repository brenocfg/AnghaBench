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
struct srp_target_port {TYPE_1__* srp_host; } ;
struct srp_device {int /*<<< orphan*/  mr_page_mask; struct ib_device* dev; } ;
struct scsi_device {int /*<<< orphan*/  request_queue; struct Scsi_Host* host; } ;
struct TYPE_4__ {int device_cap_flags; } ;
struct ib_device {TYPE_2__ attrs; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_3__ {struct srp_device* srp_dev; } ;

/* Variables and functions */
 int IB_DEVICE_SG_GAPS_REG ; 
 int /*<<< orphan*/  blk_queue_virt_boundary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct srp_target_port* host_to_target (struct Scsi_Host*) ; 

__attribute__((used)) static int srp_slave_alloc(struct scsi_device *sdev)
{
	struct Scsi_Host *shost = sdev->host;
	struct srp_target_port *target = host_to_target(shost);
	struct srp_device *srp_dev = target->srp_host->srp_dev;
	struct ib_device *ibdev = srp_dev->dev;

	if (!(ibdev->attrs.device_cap_flags & IB_DEVICE_SG_GAPS_REG))
		blk_queue_virt_boundary(sdev->request_queue,
					~srp_dev->mr_page_mask);

	return 0;
}