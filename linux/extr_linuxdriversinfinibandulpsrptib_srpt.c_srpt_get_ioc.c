#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  srp_max_rdma_size; } ;
struct srpt_port {TYPE_3__ port_attrib; struct srpt_device* sdev; } ;
struct srpt_device {int srq_size; TYPE_2__* device; scalar_t__ use_srq; } ;
struct TYPE_8__ {void* status; } ;
struct ib_dm_mad {TYPE_4__ mad_hdr; scalar_t__ data; } ;
struct ib_dm_ioc_profile {int subsys_device_id; int rdma_read_depth; int num_svc_entries; int op_cap_mask; void* rdma_size; void* send_size; void* send_queue_depth; void* protocol_version; void* protocol; void* io_subclass; void* io_class; void* subsys_vendor_id; void* device_version; void* device_id; void* vendor_id; int /*<<< orphan*/  guid; int /*<<< orphan*/  id_string; } ;
struct TYPE_5__ {unsigned int max_qp_wr; int vendor_id; int vendor_part_id; int hw_ver; } ;
struct TYPE_6__ {TYPE_1__ attrs; } ;

/* Variables and functions */
 int DM_MAD_STATUS_INVALID_FIELD ; 
 int DM_MAD_STATUS_NO_IOC ; 
 int /*<<< orphan*/  MAX_SRPT_RQ_SIZE ; 
 int /*<<< orphan*/  SRPT_ID_STRING ; 
 int SRP_IO_SUBCLASS ; 
 int SRP_PROTOCOL ; 
 int SRP_PROTOCOL_VERSION ; 
 int SRP_RDMA_READ_FROM_IOC ; 
 int SRP_RDMA_WRITE_FROM_IOC ; 
 int SRP_REV16A_IB_IO_CLASS ; 
 int SRP_SEND_FROM_IOC ; 
 int SRP_SEND_TO_IOC ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_dm_ioc_profile*,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,unsigned int) ; 
 int srp_max_req_size ; 
 int /*<<< orphan*/  srpt_service_guid ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srpt_get_ioc(struct srpt_port *sport, u32 slot,
			 struct ib_dm_mad *mad)
{
	struct srpt_device *sdev = sport->sdev;
	struct ib_dm_ioc_profile *iocp;
	int send_queue_depth;

	iocp = (struct ib_dm_ioc_profile *)mad->data;

	if (!slot || slot > 16) {
		mad->mad_hdr.status
			= cpu_to_be16(DM_MAD_STATUS_INVALID_FIELD);
		return;
	}

	if (slot > 2) {
		mad->mad_hdr.status
			= cpu_to_be16(DM_MAD_STATUS_NO_IOC);
		return;
	}

	if (sdev->use_srq)
		send_queue_depth = sdev->srq_size;
	else
		send_queue_depth = min(MAX_SRPT_RQ_SIZE,
				       sdev->device->attrs.max_qp_wr);

	memset(iocp, 0, sizeof(*iocp));
	strcpy(iocp->id_string, SRPT_ID_STRING);
	iocp->guid = cpu_to_be64(srpt_service_guid);
	iocp->vendor_id = cpu_to_be32(sdev->device->attrs.vendor_id);
	iocp->device_id = cpu_to_be32(sdev->device->attrs.vendor_part_id);
	iocp->device_version = cpu_to_be16(sdev->device->attrs.hw_ver);
	iocp->subsys_vendor_id = cpu_to_be32(sdev->device->attrs.vendor_id);
	iocp->subsys_device_id = 0x0;
	iocp->io_class = cpu_to_be16(SRP_REV16A_IB_IO_CLASS);
	iocp->io_subclass = cpu_to_be16(SRP_IO_SUBCLASS);
	iocp->protocol = cpu_to_be16(SRP_PROTOCOL);
	iocp->protocol_version = cpu_to_be16(SRP_PROTOCOL_VERSION);
	iocp->send_queue_depth = cpu_to_be16(send_queue_depth);
	iocp->rdma_read_depth = 4;
	iocp->send_size = cpu_to_be32(srp_max_req_size);
	iocp->rdma_size = cpu_to_be32(min(sport->port_attrib.srp_max_rdma_size,
					  1U << 24));
	iocp->num_svc_entries = 1;
	iocp->op_cap_mask = SRP_SEND_TO_IOC | SRP_SEND_FROM_IOC |
		SRP_RDMA_READ_FROM_IOC | SRP_RDMA_WRITE_FROM_IOC;

	mad->mad_hdr.status = 0;
}