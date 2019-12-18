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
struct Scsi_Host {int max_lun; int this_id; int irq; TYPE_1__* hostt; int /*<<< orphan*/  sg_tablesize; int /*<<< orphan*/  cmd_per_lun; int /*<<< orphan*/  can_queue; int /*<<< orphan*/  host_no; } ;
struct NCR5380_hostdata {int id_mask; int id_higher_mask; int flags; unsigned long poll_loops; int /*<<< orphan*/  info; int /*<<< orphan*/  base; int /*<<< orphan*/  io_port; int /*<<< orphan*/  work_q; int /*<<< orphan*/  main_task; int /*<<< orphan*/  disconnected; int /*<<< orphan*/  unissued; int /*<<< orphan*/  autosense; int /*<<< orphan*/ * sensing; int /*<<< orphan*/ * connected; int /*<<< orphan*/  lock; scalar_t__ dma_len; scalar_t__* busy; struct Scsi_Host* host; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FLAG_DMA_FIXUP ; 
 int FLAG_NO_PSEUDO_DMA ; 
 int FLAG_TOSHIBA_DELAY ; 
 int /*<<< orphan*/  ICR_BASE ; 
 int /*<<< orphan*/  INITIATOR_COMMAND_REG ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODE_REG ; 
 int /*<<< orphan*/  MR_BASE ; 
 unsigned long NCR5380_REG_POLL_TIME ; 
 int /*<<< orphan*/  NCR5380_main ; 
 int /*<<< orphan*/  NCR5380_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCR5380_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELECT_ENABLE_REG ; 
 int /*<<< orphan*/  STATUS_REG ; 
 int /*<<< orphan*/  TARGET_COMMAND_REG ; 
 int WQ_MEM_RECLAIM ; 
 int WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct NCR5380_hostdata* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 

__attribute__((used)) static int NCR5380_init(struct Scsi_Host *instance, int flags)
{
	struct NCR5380_hostdata *hostdata = shost_priv(instance);
	int i;
	unsigned long deadline;
	unsigned long accesses_per_ms;

	instance->max_lun = 7;

	hostdata->host = instance;
	hostdata->id_mask = 1 << instance->this_id;
	hostdata->id_higher_mask = 0;
	for (i = hostdata->id_mask; i <= 0x80; i <<= 1)
		if (i > hostdata->id_mask)
			hostdata->id_higher_mask |= i;
	for (i = 0; i < 8; ++i)
		hostdata->busy[i] = 0;
	hostdata->dma_len = 0;

	spin_lock_init(&hostdata->lock);
	hostdata->connected = NULL;
	hostdata->sensing = NULL;
	INIT_LIST_HEAD(&hostdata->autosense);
	INIT_LIST_HEAD(&hostdata->unissued);
	INIT_LIST_HEAD(&hostdata->disconnected);

	hostdata->flags = flags;

	INIT_WORK(&hostdata->main_task, NCR5380_main);
	hostdata->work_q = alloc_workqueue("ncr5380_%d",
	                        WQ_UNBOUND | WQ_MEM_RECLAIM,
	                        1, instance->host_no);
	if (!hostdata->work_q)
		return -ENOMEM;

	snprintf(hostdata->info, sizeof(hostdata->info),
		"%s, irq %d, io_port 0x%lx, base 0x%lx, can_queue %d, cmd_per_lun %d, sg_tablesize %d, this_id %d, flags { %s%s%s}",
		instance->hostt->name, instance->irq, hostdata->io_port,
		hostdata->base, instance->can_queue, instance->cmd_per_lun,
		instance->sg_tablesize, instance->this_id,
		hostdata->flags & FLAG_DMA_FIXUP     ? "DMA_FIXUP "     : "",
		hostdata->flags & FLAG_NO_PSEUDO_DMA ? "NO_PSEUDO_DMA " : "",
		hostdata->flags & FLAG_TOSHIBA_DELAY ? "TOSHIBA_DELAY " : "");

	NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
	NCR5380_write(MODE_REG, MR_BASE);
	NCR5380_write(TARGET_COMMAND_REG, 0);
	NCR5380_write(SELECT_ENABLE_REG, 0);

	/* Calibrate register polling loop */
	i = 0;
	deadline = jiffies + 1;
	do {
		cpu_relax();
	} while (time_is_after_jiffies(deadline));
	deadline += msecs_to_jiffies(256);
	do {
		NCR5380_read(STATUS_REG);
		++i;
		cpu_relax();
	} while (time_is_after_jiffies(deadline));
	accesses_per_ms = i / 256;
	hostdata->poll_loops = NCR5380_REG_POLL_TIME * accesses_per_ms / 2;

	return 0;
}