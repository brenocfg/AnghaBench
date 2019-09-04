#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int /*<<< orphan*/  request_queue; } ;
struct TYPE_7__ {TYPE_1__* device; } ;
struct iser_conn {TYPE_2__ ib_conn; } ;
struct iscsi_session {TYPE_4__* leadconn; } ;
struct TYPE_8__ {int device_cap_flags; } ;
struct ib_device {TYPE_3__ attrs; } ;
struct TYPE_10__ {struct iscsi_session* dd_data; } ;
struct TYPE_9__ {struct iser_conn* dd_data; } ;
struct TYPE_6__ {struct ib_device* ib_device; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int IB_DEVICE_SG_GAPS_REG ; 
 int /*<<< orphan*/  MASK_4K ; 
 int /*<<< orphan*/  blk_queue_virt_boundary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_target (struct scsi_device*) ; 
 TYPE_5__* starget_to_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unbind_iser_conn_mutex ; 

__attribute__((used)) static int iscsi_iser_slave_alloc(struct scsi_device *sdev)
{
	struct iscsi_session *session;
	struct iser_conn *iser_conn;
	struct ib_device *ib_dev;

	mutex_lock(&unbind_iser_conn_mutex);

	session = starget_to_session(scsi_target(sdev))->dd_data;
	iser_conn = session->leadconn->dd_data;
	if (!iser_conn) {
		mutex_unlock(&unbind_iser_conn_mutex);
		return -ENOTCONN;
	}
	ib_dev = iser_conn->ib_conn.device->ib_device;

	if (!(ib_dev->attrs.device_cap_flags & IB_DEVICE_SG_GAPS_REG))
		blk_queue_virt_boundary(sdev->request_queue, ~MASK_4K);

	mutex_unlock(&unbind_iser_conn_mutex);

	return 0;
}