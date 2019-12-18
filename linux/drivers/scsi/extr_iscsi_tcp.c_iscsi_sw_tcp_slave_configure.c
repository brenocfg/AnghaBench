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
struct scsi_device {TYPE_2__* request_queue; int /*<<< orphan*/  host; } ;
struct iscsi_sw_tcp_host {struct iscsi_session* session; } ;
struct iscsi_session {struct iscsi_conn* leadconn; } ;
struct iscsi_conn {scalar_t__ datadgst_en; } ;
struct TYPE_4__ {TYPE_1__* backing_dev_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_CAP_STABLE_WRITES ; 
 int /*<<< orphan*/  blk_queue_dma_alignment (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct iscsi_sw_tcp_host* iscsi_host_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_sw_tcp_slave_configure(struct scsi_device *sdev)
{
	struct iscsi_sw_tcp_host *tcp_sw_host = iscsi_host_priv(sdev->host);
	struct iscsi_session *session = tcp_sw_host->session;
	struct iscsi_conn *conn = session->leadconn;

	if (conn->datadgst_en)
		sdev->request_queue->backing_dev_info->capabilities
			|= BDI_CAP_STABLE_WRITES;
	blk_queue_dma_alignment(sdev->request_queue, 0);
	return 0;
}