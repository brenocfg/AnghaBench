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
typedef  int u32 ;
struct queue_limits {int physical_block_size; int logical_block_size; int const discard_granularity; int const io_opt; } ;
struct nvme_id_ns {int nsfeat; void* nows; void* npdg; void* npda; void* npwg; void* npwa; void* nacwu; void* nawupf; void* nawun; } ;
struct block_device {int dummy; } ;
typedef  void* __le16 ;
struct TYPE_2__ {struct queue_limits limits; } ;

/* Variables and functions */
 TYPE_1__* bdev_get_queue (struct block_device*) ; 
 void* to0based (int const) ; 

void nvmet_bdev_set_limits(struct block_device *bdev, struct nvme_id_ns *id)
{
	const struct queue_limits *ql = &bdev_get_queue(bdev)->limits;
	/* Number of logical blocks per physical block. */
	const u32 lpp = ql->physical_block_size / ql->logical_block_size;
	/* Logical blocks per physical block, 0's based. */
	const __le16 lpp0b = to0based(lpp);

	/*
	 * For NVMe 1.2 and later, bit 1 indicates that the fields NAWUN,
	 * NAWUPF, and NACWU are defined for this namespace and should be
	 * used by the host for this namespace instead of the AWUN, AWUPF,
	 * and ACWU fields in the Identify Controller data structure. If
	 * any of these fields are zero that means that the corresponding
	 * field from the identify controller data structure should be used.
	 */
	id->nsfeat |= 1 << 1;
	id->nawun = lpp0b;
	id->nawupf = lpp0b;
	id->nacwu = lpp0b;

	/*
	 * Bit 4 indicates that the fields NPWG, NPWA, NPDG, NPDA, and
	 * NOWS are defined for this namespace and should be used by
	 * the host for I/O optimization.
	 */
	id->nsfeat |= 1 << 4;
	/* NPWG = Namespace Preferred Write Granularity. 0's based */
	id->npwg = lpp0b;
	/* NPWA = Namespace Preferred Write Alignment. 0's based */
	id->npwa = id->npwg;
	/* NPDG = Namespace Preferred Deallocate Granularity. 0's based */
	id->npdg = to0based(ql->discard_granularity / ql->logical_block_size);
	/* NPDG = Namespace Preferred Deallocate Alignment */
	id->npda = id->npdg;
	/* NOWS = Namespace Optimal Write Size */
	id->nows = to0based(ql->io_opt / ql->logical_block_size);
}