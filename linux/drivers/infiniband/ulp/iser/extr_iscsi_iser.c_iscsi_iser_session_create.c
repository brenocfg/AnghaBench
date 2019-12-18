#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u32 ;
struct ib_conn {scalar_t__ pi_support; TYPE_1__* device; } ;
struct iser_conn {int scsi_sg_tablesize; scalar_t__ state; int /*<<< orphan*/  state_mutex; struct ib_conn ib_conn; int /*<<< orphan*/  max_cmds; } ;
struct iscsi_iser_task {int dummy; } ;
struct iscsi_endpoint {struct iser_conn* dd_data; } ;
struct iscsi_cls_session {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_5__ {int sig_prot_cap; int device_cap_flags; } ;
struct ib_device {TYPE_3__ dev; TYPE_2__ attrs; } ;
struct Scsi_Host {int max_cmd_len; int sg_tablesize; scalar_t__ max_sectors; void* can_queue; int /*<<< orphan*/  virt_boundary_mask; scalar_t__ max_channel; scalar_t__ max_id; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  cmd_per_lun; int /*<<< orphan*/  transportt; } ;
struct TYPE_4__ {struct ib_device* ib_device; } ;

/* Variables and functions */
 int IB_DEVICE_SG_GAPS_REG ; 
 scalar_t__ ISER_CONN_UP ; 
 int /*<<< orphan*/  ISER_DEF_XMIT_CMDS_MAX ; 
 int /*<<< orphan*/  MASK_4K ; 
 int PAGE_SIZE ; 
 int SHOST_DIX_GUARD_CRC ; 
 int SHOST_DIX_GUARD_IP ; 
 scalar_t__ iscsi_host_add (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* iscsi_host_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_host_free (struct Scsi_Host*) ; 
 int /*<<< orphan*/  iscsi_host_remove (struct Scsi_Host*) ; 
 int /*<<< orphan*/  iscsi_iser_scsi_transport ; 
 int /*<<< orphan*/  iscsi_iser_sht ; 
 int /*<<< orphan*/  iscsi_iser_transport ; 
 int /*<<< orphan*/  iscsi_max_lun ; 
 struct iscsi_cls_session* iscsi_session_setup (int /*<<< orphan*/ *,struct Scsi_Host*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_dbg (char*,struct iser_conn*,int,scalar_t__) ; 
 int /*<<< orphan*/  iser_dif_prot_caps (int) ; 
 int /*<<< orphan*/  iser_err (char*,struct iser_conn*) ; 
 scalar_t__ iser_max_sectors ; 
 int /*<<< orphan*/  iser_warn (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,int) ; 
 void* min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_set_guard (struct Scsi_Host*,int) ; 
 int /*<<< orphan*/  scsi_host_set_prot (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static struct iscsi_cls_session *
iscsi_iser_session_create(struct iscsi_endpoint *ep,
			  uint16_t cmds_max, uint16_t qdepth,
			  uint32_t initial_cmdsn)
{
	struct iscsi_cls_session *cls_session;
	struct Scsi_Host *shost;
	struct iser_conn *iser_conn = NULL;
	struct ib_conn *ib_conn;
	struct ib_device *ib_dev;
	u32 max_fr_sectors;

	shost = iscsi_host_alloc(&iscsi_iser_sht, 0, 0);
	if (!shost)
		return NULL;
	shost->transportt = iscsi_iser_scsi_transport;
	shost->cmd_per_lun = qdepth;
	shost->max_lun = iscsi_max_lun;
	shost->max_id = 0;
	shost->max_channel = 0;
	shost->max_cmd_len = 16;

	/*
	 * older userspace tools (before 2.0-870) did not pass us
	 * the leading conn's ep so this will be NULL;
	 */
	if (ep) {
		iser_conn = ep->dd_data;
		shost->sg_tablesize = iser_conn->scsi_sg_tablesize;
		shost->can_queue = min_t(u16, cmds_max, iser_conn->max_cmds);

		mutex_lock(&iser_conn->state_mutex);
		if (iser_conn->state != ISER_CONN_UP) {
			iser_err("iser conn %p already started teardown\n",
				 iser_conn);
			mutex_unlock(&iser_conn->state_mutex);
			goto free_host;
		}

		ib_conn = &iser_conn->ib_conn;
		ib_dev = ib_conn->device->ib_device;
		if (ib_conn->pi_support) {
			u32 sig_caps = ib_dev->attrs.sig_prot_cap;

			scsi_host_set_prot(shost, iser_dif_prot_caps(sig_caps));
			scsi_host_set_guard(shost, SHOST_DIX_GUARD_IP |
						   SHOST_DIX_GUARD_CRC);
		}

		if (!(ib_dev->attrs.device_cap_flags & IB_DEVICE_SG_GAPS_REG))
			shost->virt_boundary_mask = ~MASK_4K;

		if (iscsi_host_add(shost, ib_dev->dev.parent)) {
			mutex_unlock(&iser_conn->state_mutex);
			goto free_host;
		}
		mutex_unlock(&iser_conn->state_mutex);
	} else {
		shost->can_queue = min_t(u16, cmds_max, ISER_DEF_XMIT_CMDS_MAX);
		if (iscsi_host_add(shost, NULL))
			goto free_host;
	}

	max_fr_sectors = (shost->sg_tablesize * PAGE_SIZE) >> 9;
	shost->max_sectors = min(iser_max_sectors, max_fr_sectors);

	iser_dbg("iser_conn %p, sg_tablesize %u, max_sectors %u\n",
		 iser_conn, shost->sg_tablesize,
		 shost->max_sectors);

	if (shost->max_sectors < iser_max_sectors)
		iser_warn("max_sectors was reduced from %u to %u\n",
			  iser_max_sectors, shost->max_sectors);

	cls_session = iscsi_session_setup(&iscsi_iser_transport, shost,
					  shost->can_queue, 0,
					  sizeof(struct iscsi_iser_task),
					  initial_cmdsn, 0);
	if (!cls_session)
		goto remove_host;

	return cls_session;

remove_host:
	iscsi_host_remove(shost);
free_host:
	iscsi_host_free(shost);
	return NULL;
}