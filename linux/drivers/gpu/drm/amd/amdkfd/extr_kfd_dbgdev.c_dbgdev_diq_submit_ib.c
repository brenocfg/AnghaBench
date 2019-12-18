#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int low_part; int /*<<< orphan*/  high_part; } ;
union ULARGE_INTEGER {TYPE_8__ u; int /*<<< orphan*/  quad_part; } ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_20__ {int /*<<< orphan*/  dst_sel; int /*<<< orphan*/  int_sel; int /*<<< orphan*/  data_sel; } ;
struct TYPE_18__ {int address_lo_32b; } ;
struct TYPE_17__ {int tc_wb_action_ena; scalar_t__ atc; int /*<<< orphan*/  cache_policy; int /*<<< orphan*/  event_index; int /*<<< orphan*/  event_type; } ;
struct TYPE_16__ {int count; void* type; int /*<<< orphan*/  opcode; } ;
struct pm4__release_mem {int /*<<< orphan*/  data_lo; TYPE_9__ bitfields3; int /*<<< orphan*/  address_hi; TYPE_7__ bitfields4; TYPE_6__ bitfields2; TYPE_5__ header; } ;
struct TYPE_15__ {unsigned int pasid; } ;
struct TYPE_14__ {int /*<<< orphan*/  ib_base_hi; } ;
struct TYPE_13__ {int ib_base_lo; } ;
struct TYPE_12__ {int count; void* type; int /*<<< orphan*/  opcode; } ;
struct pm4__indirect_buffer_pasid {int control; TYPE_4__ bitfields5; TYPE_3__ bitfields3; TYPE_2__ bitfields2; TYPE_1__ header; } ;
struct kfd_mem_obj {int /*<<< orphan*/  gpu_addr; scalar_t__ cpu_ptr; } ;
struct kfd_dbgdev {int /*<<< orphan*/  dev; struct kernel_queue* kq; } ;
struct TYPE_11__ {int (* acquire_packet_buffer ) (struct kernel_queue*,size_t,unsigned int**) ;int /*<<< orphan*/  (* submit_packet ) (struct kernel_queue*) ;int /*<<< orphan*/  (* rollback_packet ) (struct kernel_queue*) ;} ;
struct kernel_queue {TYPE_10__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_FLUSH_AND_INV_TS_EVENT ; 
 int EINVAL ; 
 int /*<<< orphan*/  IT_INDIRECT_BUFFER_PASID ; 
 int /*<<< orphan*/  IT_RELEASE_MEM ; 
 void* PM4_TYPE_3 ; 
 int /*<<< orphan*/  QUEUESTATE__ACTIVE ; 
 int /*<<< orphan*/  QUEUESTATE__ACTIVE_COMPLETION_PENDING ; 
 scalar_t__ WARN_ON (int) ; 
 int amdkfd_fence_wait_timeout (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cache_policy___release_mem__lru ; 
 int /*<<< orphan*/  data_sel___release_mem__send_64_bit_data ; 
 int /*<<< orphan*/  dst_sel___release_mem__memory_controller ; 
 int /*<<< orphan*/  event_index___release_mem__end_of_pipe ; 
 int /*<<< orphan*/  int_sel___release_mem__send_data_after_write_confirm ; 
 int kfd_gtt_sa_allocate (int /*<<< orphan*/ ,int,struct kfd_mem_obj**) ; 
 int /*<<< orphan*/  kfd_gtt_sa_free (int /*<<< orphan*/ ,struct kfd_mem_obj*) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (struct kernel_queue*,size_t,unsigned int**) ; 
 int /*<<< orphan*/  stub2 (struct kernel_queue*) ; 
 int /*<<< orphan*/  stub3 (struct kernel_queue*) ; 

__attribute__((used)) static int dbgdev_diq_submit_ib(struct kfd_dbgdev *dbgdev,
				unsigned int pasid, uint64_t vmid0_address,
				uint32_t *packet_buff, size_t size_in_bytes)
{
	struct pm4__release_mem *rm_packet;
	struct pm4__indirect_buffer_pasid *ib_packet;
	struct kfd_mem_obj *mem_obj;
	size_t pq_packets_size_in_bytes;
	union ULARGE_INTEGER *largep;
	union ULARGE_INTEGER addr;
	struct kernel_queue *kq;
	uint64_t *rm_state;
	unsigned int *ib_packet_buff;
	int status;

	if (WARN_ON(!size_in_bytes))
		return -EINVAL;

	kq = dbgdev->kq;

	pq_packets_size_in_bytes = sizeof(struct pm4__release_mem) +
				sizeof(struct pm4__indirect_buffer_pasid);

	/*
	 * We acquire a buffer from DIQ
	 * The receive packet buff will be sitting on the Indirect Buffer
	 * and in the PQ we put the IB packet + sync packet(s).
	 */
	status = kq->ops.acquire_packet_buffer(kq,
				pq_packets_size_in_bytes / sizeof(uint32_t),
				&ib_packet_buff);
	if (status) {
		pr_err("acquire_packet_buffer failed\n");
		return status;
	}

	memset(ib_packet_buff, 0, pq_packets_size_in_bytes);

	ib_packet = (struct pm4__indirect_buffer_pasid *) (ib_packet_buff);

	ib_packet->header.count = 3;
	ib_packet->header.opcode = IT_INDIRECT_BUFFER_PASID;
	ib_packet->header.type = PM4_TYPE_3;

	largep = (union ULARGE_INTEGER *) &vmid0_address;

	ib_packet->bitfields2.ib_base_lo = largep->u.low_part >> 2;
	ib_packet->bitfields3.ib_base_hi = largep->u.high_part;

	ib_packet->control = (1 << 23) | (1 << 31) |
			((size_in_bytes / 4) & 0xfffff);

	ib_packet->bitfields5.pasid = pasid;

	/*
	 * for now we use release mem for GPU-CPU synchronization
	 * Consider WaitRegMem + WriteData as a better alternative
	 * we get a GART allocations ( gpu/cpu mapping),
	 * for the sync variable, and wait until:
	 * (a) Sync with HW
	 * (b) Sync var is written by CP to mem.
	 */
	rm_packet = (struct pm4__release_mem *) (ib_packet_buff +
			(sizeof(struct pm4__indirect_buffer_pasid) /
					sizeof(unsigned int)));

	status = kfd_gtt_sa_allocate(dbgdev->dev, sizeof(uint64_t),
					&mem_obj);

	if (status) {
		pr_err("Failed to allocate GART memory\n");
		kq->ops.rollback_packet(kq);
		return status;
	}

	rm_state = (uint64_t *) mem_obj->cpu_ptr;

	*rm_state = QUEUESTATE__ACTIVE_COMPLETION_PENDING;

	rm_packet->header.opcode = IT_RELEASE_MEM;
	rm_packet->header.type = PM4_TYPE_3;
	rm_packet->header.count = sizeof(struct pm4__release_mem) / 4 - 2;

	rm_packet->bitfields2.event_type = CACHE_FLUSH_AND_INV_TS_EVENT;
	rm_packet->bitfields2.event_index =
				event_index___release_mem__end_of_pipe;

	rm_packet->bitfields2.cache_policy = cache_policy___release_mem__lru;
	rm_packet->bitfields2.atc = 0;
	rm_packet->bitfields2.tc_wb_action_ena = 1;

	addr.quad_part = mem_obj->gpu_addr;

	rm_packet->bitfields4.address_lo_32b = addr.u.low_part >> 2;
	rm_packet->address_hi = addr.u.high_part;

	rm_packet->bitfields3.data_sel =
				data_sel___release_mem__send_64_bit_data;

	rm_packet->bitfields3.int_sel =
			int_sel___release_mem__send_data_after_write_confirm;

	rm_packet->bitfields3.dst_sel =
			dst_sel___release_mem__memory_controller;

	rm_packet->data_lo = QUEUESTATE__ACTIVE;

	kq->ops.submit_packet(kq);

	/* Wait till CP writes sync code: */
	status = amdkfd_fence_wait_timeout(
			(unsigned int *) rm_state,
			QUEUESTATE__ACTIVE, 1500);

	kfd_gtt_sa_free(dbgdev->dev, mem_obj);

	return status;
}