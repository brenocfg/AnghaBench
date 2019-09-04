#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  q_no; } ;
union oct_txpciq {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  size_t u32 ;
struct octeon_instr_queue {int dummy; } ;
struct TYPE_12__ {scalar_t__ (* enable_io_queues ) (struct octeon_device*) ;} ;
struct octeon_device {TYPE_4__ fn_list; int /*<<< orphan*/  num_iqs; TYPE_5__** instr_queue; TYPE_2__* pci_dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  u64; } ;
struct TYPE_13__ {int q_index; int ifidx; void* app_ctx; TYPE_3__ txpciq; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ octeon_init_instr_queue (struct octeon_device*,union oct_txpciq,size_t) ; 
 scalar_t__ stub1 (struct octeon_device*) ; 
 int /*<<< orphan*/  vfree (TYPE_5__*) ; 
 TYPE_5__* vmalloc (int) ; 
 TYPE_5__* vmalloc_node (int,int) ; 

int octeon_setup_iq(struct octeon_device *oct,
		    int ifidx,
		    int q_index,
		    union oct_txpciq txpciq,
		    u32 num_descs,
		    void *app_ctx)
{
	u32 iq_no = (u32)txpciq.s.q_no;
	int numa_node = dev_to_node(&oct->pci_dev->dev);

	if (oct->instr_queue[iq_no]) {
		dev_dbg(&oct->pci_dev->dev, "IQ is in use. Cannot create the IQ: %d again\n",
			iq_no);
		oct->instr_queue[iq_no]->txpciq.u64 = txpciq.u64;
		oct->instr_queue[iq_no]->app_ctx = app_ctx;
		return 0;
	}
	oct->instr_queue[iq_no] =
	    vmalloc_node(sizeof(struct octeon_instr_queue), numa_node);
	if (!oct->instr_queue[iq_no])
		oct->instr_queue[iq_no] =
		    vmalloc(sizeof(struct octeon_instr_queue));
	if (!oct->instr_queue[iq_no])
		return 1;

	memset(oct->instr_queue[iq_no], 0,
	       sizeof(struct octeon_instr_queue));

	oct->instr_queue[iq_no]->q_index = q_index;
	oct->instr_queue[iq_no]->app_ctx = app_ctx;
	oct->instr_queue[iq_no]->ifidx = ifidx;

	if (octeon_init_instr_queue(oct, txpciq, num_descs)) {
		vfree(oct->instr_queue[iq_no]);
		oct->instr_queue[iq_no] = NULL;
		return 1;
	}

	oct->num_iqs++;
	if (oct->fn_list.enable_io_queues(oct))
		return 1;

	return 0;
}