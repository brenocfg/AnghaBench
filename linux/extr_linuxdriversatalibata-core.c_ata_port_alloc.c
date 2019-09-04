#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ata_port {int pflags; int print_id; int local_port_no; int msg_enable; int /*<<< orphan*/  link; int /*<<< orphan*/  cbl; int /*<<< orphan*/  fastdrain_timer; int /*<<< orphan*/  park_req_pending; int /*<<< orphan*/  eh_wait_q; int /*<<< orphan*/  eh_done_q; int /*<<< orphan*/  scsi_rescan_task; int /*<<< orphan*/  hotplug_task; int /*<<< orphan*/  scsi_scan_mutex; int /*<<< orphan*/  dev; struct ata_host* host; int /*<<< orphan*/ * lock; } ;
struct ata_host {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_NONE ; 
 int ATA_MSG_DRV ; 
 int ATA_MSG_ERR ; 
 int ATA_MSG_WARN ; 
 int ATA_PFLAG_FROZEN ; 
 int ATA_PFLAG_INITIALIZING ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_DEFERRABLE ; 
 int /*<<< orphan*/  ata_eh_fastdrain_timerfn ; 
 int /*<<< orphan*/  ata_link_init (struct ata_port*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_scsi_dev_rescan ; 
 int /*<<< orphan*/  ata_scsi_hotplug ; 
 int /*<<< orphan*/  ata_sff_port_init (struct ata_port*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct ata_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ata_port *ata_port_alloc(struct ata_host *host)
{
	struct ata_port *ap;

	DPRINTK("ENTER\n");

	ap = kzalloc(sizeof(*ap), GFP_KERNEL);
	if (!ap)
		return NULL;

	ap->pflags |= ATA_PFLAG_INITIALIZING | ATA_PFLAG_FROZEN;
	ap->lock = &host->lock;
	ap->print_id = -1;
	ap->local_port_no = -1;
	ap->host = host;
	ap->dev = host->dev;

#if defined(ATA_VERBOSE_DEBUG)
	/* turn on all debugging levels */
	ap->msg_enable = 0x00FF;
#elif defined(ATA_DEBUG)
	ap->msg_enable = ATA_MSG_DRV | ATA_MSG_INFO | ATA_MSG_CTL | ATA_MSG_WARN | ATA_MSG_ERR;
#else
	ap->msg_enable = ATA_MSG_DRV | ATA_MSG_ERR | ATA_MSG_WARN;
#endif

	mutex_init(&ap->scsi_scan_mutex);
	INIT_DELAYED_WORK(&ap->hotplug_task, ata_scsi_hotplug);
	INIT_WORK(&ap->scsi_rescan_task, ata_scsi_dev_rescan);
	INIT_LIST_HEAD(&ap->eh_done_q);
	init_waitqueue_head(&ap->eh_wait_q);
	init_completion(&ap->park_req_pending);
	timer_setup(&ap->fastdrain_timer, ata_eh_fastdrain_timerfn,
		    TIMER_DEFERRABLE);

	ap->cbl = ATA_CBL_NONE;

	ata_link_init(ap, &ap->link, 0);

#ifdef ATA_IRQ_TRAP
	ap->stats.unhandled_irq = 1;
	ap->stats.idle_irq = 1;
#endif
	ata_sff_port_init(ap);

	return ap;
}