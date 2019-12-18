#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {char* ptr; } ;
struct scsi_cmnd {TYPE_1__ SCp; } ;
struct gdth_cmndinfo {scalar_t__ priority; int /*<<< orphan*/  internal_command; } ;
struct TYPE_5__ {struct scsi_cmnd* req_first; int /*<<< orphan*/  smp_lock; } ;
typedef  TYPE_2__ gdth_ha_str ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRACE3 (char*) ; 
 struct gdth_cmndinfo* gdth_cmnd_priv (struct scsi_cmnd*) ; 
 unsigned long max_rq ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gdth_putq(gdth_ha_str *ha, struct scsi_cmnd *scp, u8 priority)
{
    struct gdth_cmndinfo *cmndinfo = gdth_cmnd_priv(scp);
    register struct scsi_cmnd *pscp;
    register struct scsi_cmnd *nscp;
    unsigned long flags;

    TRACE(("gdth_putq() priority %d\n",priority));
    spin_lock_irqsave(&ha->smp_lock, flags);

    if (!cmndinfo->internal_command)
        cmndinfo->priority = priority;

    if (ha->req_first==NULL) {
        ha->req_first = scp;                    /* queue was empty */
        scp->SCp.ptr = NULL;
    } else {                                    /* queue not empty */
        pscp = ha->req_first;
        nscp = (struct scsi_cmnd *)pscp->SCp.ptr;
        /* priority: 0-highest,..,0xff-lowest */
        while (nscp && gdth_cmnd_priv(nscp)->priority <= priority) {
            pscp = nscp;
            nscp = (struct scsi_cmnd *)pscp->SCp.ptr;
        }
        pscp->SCp.ptr = (char *)scp;
        scp->SCp.ptr  = (char *)nscp;
    }
    spin_unlock_irqrestore(&ha->smp_lock, flags);

#ifdef GDTH_STATISTICS
    flags = 0;
    for (nscp=ha->req_first; nscp; nscp=(struct scsi_cmnd*)nscp->SCp.ptr)
        ++flags;
    if (max_rq < flags) {
        max_rq = flags;
        TRACE3(("GDT: max_rq = %d\n",(u16)max_rq));
    }
#endif
}