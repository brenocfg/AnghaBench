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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  ib_base_hi; } ;
struct TYPE_7__ {size_t ib_size; int chain; int valid; int process_cnt; scalar_t__ offload_polling; } ;
struct TYPE_6__ {int /*<<< orphan*/  u32All; } ;
struct pm4_mes_runlist {TYPE_4__ bitfields3; int /*<<< orphan*/  ordinal2; TYPE_3__ bitfields4; TYPE_2__ header; } ;
struct packet_manager {TYPE_1__* dqm; } ;
struct kfd_dev {int /*<<< orphan*/  max_proc_per_quantum; } ;
struct TYPE_5__ {int /*<<< orphan*/  processes_count; struct kfd_dev* dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  IT_RUN_LIST ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_build_pm4_header (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm_runlist_vi(struct packet_manager *pm, uint32_t *buffer,
			uint64_t ib, size_t ib_size_in_dwords, bool chain)
{
	struct pm4_mes_runlist *packet;
	int concurrent_proc_cnt = 0;
	struct kfd_dev *kfd = pm->dqm->dev;

	if (WARN_ON(!ib))
		return -EFAULT;

	/* Determine the number of processes to map together to HW:
	 * it can not exceed the number of VMIDs available to the
	 * scheduler, and it is determined by the smaller of the number
	 * of processes in the runlist and kfd module parameter
	 * hws_max_conc_proc.
	 * Note: the arbitration between the number of VMIDs and
	 * hws_max_conc_proc has been done in
	 * kgd2kfd_device_init().
	 */
	concurrent_proc_cnt = min(pm->dqm->processes_count,
			kfd->max_proc_per_quantum);

	packet = (struct pm4_mes_runlist *)buffer;

	memset(buffer, 0, sizeof(struct pm4_mes_runlist));
	packet->header.u32All = pm_build_pm4_header(IT_RUN_LIST,
						sizeof(struct pm4_mes_runlist));

	packet->bitfields4.ib_size = ib_size_in_dwords;
	packet->bitfields4.chain = chain ? 1 : 0;
	packet->bitfields4.offload_polling = 0;
	packet->bitfields4.valid = 1;
	packet->bitfields4.process_cnt = concurrent_proc_cnt;
	packet->ordinal2 = lower_32_bits(ib);
	packet->bitfields3.ib_base_hi = upper_32_bits(ib);

	return 0;
}